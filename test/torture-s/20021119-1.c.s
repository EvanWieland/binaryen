	.text
	.file	"/b/build/slave/linux/build/src/buildbot/work/gcc/gcc/testsuite/gcc.c-torture/execute/20021119-1.c"
	.globl	foo
	.type	foo,@function
foo:                                    # @foo
	.param  	i32
	.result 	i32
# BB#0:                                 # %entry
	i32.const	$push2=, 80
	i32.const	$push0=, 2
	i32.shl 	$push1=, $0, $pop0
	i32.sub 	$push3=, $pop2, $pop1
	i32.const	$push4=, 20
	i32.div_s	$push5=, $pop3, $pop4
	return  	$pop5
func_end0:
	.size	foo, func_end0-foo

	.globl	main
	.type	main,@function
main:                                   # @main
	.result 	i32
# BB#0:                                 # %if.end
	i32.const	$push0=, 0
	return  	$pop0
func_end1:
	.size	main, func_end1-main


	.ident	"clang version 3.8.0 "
	.section	".note.GNU-stack","",@progbits