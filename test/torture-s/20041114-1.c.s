	.text
	.file	"/b/build/slave/linux/build/src/buildbot/work/gcc/gcc/testsuite/gcc.c-torture/execute/20041114-1.c"
	.globl	foo
	.type	foo,@function
foo:                                    # @foo
	.param  	i32
# BB#0:                                 # %entry
	return
func_end0:
	.size	foo, func_end0-foo

	.globl	main
	.type	main,@function
main:                                   # @main
	.param  	i32, i32
	.result 	i32
	.local  	i32
# BB#0:                                 # %entry
	i32.const	$2=, 0
	i32.load	$discard=, v($2)
	return  	$2
func_end1:
	.size	main, func_end1-main

	.type	v,@object               # @v
	.bss
	.globl	v
	.align	2
v:
	.int32	0                       # 0x0
	.size	v, 4


	.ident	"clang version 3.8.0 "
	.section	".note.GNU-stack","",@progbits