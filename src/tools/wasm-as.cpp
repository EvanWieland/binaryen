/*
 * Copyright 2016 WebAssembly Community Group participants
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//
// wasm2asm console tool
//

#include "support/colors.h"
#include "support/command-line.h"
#include "support/file.h"
#include "wasm-binary.h"
#include "wasm-s-parser.h"

using namespace cashew;
using namespace wasm;

int main(int argc, const char *argv[]) {
  bool debugInfo = false;
  Options options("wasm-as", "Assemble a .wast (WebAssembly text format) into a .wasm (WebAssembly binary format)");
  options.extra["validate"] = "wasm";
  options
      .add("--output", "-o", "Output file (stdout if not specified)",
           Options::Arguments::One,
           [](Options *o, const std::string &argument) {
             o->extra["output"] = argument;
             Colors::disable();
           })
      .add("--validate", "-v", "Control validation of the output module",
           Options::Arguments::One,
           [](Options *o, const std::string &argument) {
             if (argument != "web" && argument != "none" && argument != "wasm") {
               std::cerr << "Valid arguments for --validate flag are 'wasm', 'web', and 'none'.\n";
               exit(1);
             }
             o->extra["validate"] = argument;
           })
      .add("--debuginfo", "-g", "Emit names section and debug info",
           Options::Arguments::Zero,
           [&](Options *o, const std::string &arguments) { debugInfo = true; })
      .add_positional("INFILE", Options::Arguments::One,
                      [](Options *o, const std::string &argument) {
                        o->extra["infile"] = argument;
                      });
  options.parse(argc, argv);

  auto input(read_file<std::string>(options.extra["infile"], Flags::Text, options.debug ? Flags::Debug : Flags::Release));

  Module wasm;

  try {
    if (options.debug) std::cerr << "s-parsing..." << std::endl;
    SExpressionParser parser(const_cast<char*>(input.c_str()));
    Element& root = *parser.root;
    if (options.debug) std::cerr << "w-parsing..." << std::endl;
    SExpressionWasmBuilder builder(wasm, *root[0]);
  } catch (ParseException& p) {
    p.dump(std::cerr);
    Fatal() << "error in parsing input";
  }

  if (options.extra["validate"] != "none") {
    if (options.debug) std::cerr << "Validating..." << std::endl;
    if (!wasm::WasmValidator().validate(wasm,
        options.extra["validate"] == "web")) {
      Fatal() << "Error: input module is not valid.\n";
    }
  }

  if (options.debug) std::cerr << "binarification..." << std::endl;
  BufferWithRandomAccess buffer(options.debug);
  WasmBinaryWriter writer(&wasm, buffer, options.debug);
  writer.setDebugInfo(debugInfo);
  writer.write();

  if (options.debug) std::cerr << "writing to output..." << std::endl;
  Output output(options.extra["output"], Flags::Binary, options.debug ? Flags::Debug : Flags::Release);
  buffer.writeTo(output);

  if (options.debug) std::cerr << "Done." << std::endl;
}
