	.text
	.file	"/b/build/slave/linux/build/src/buildbot/work/gcc/gcc/testsuite/gcc.c-torture/execute/960801-1.c"
	.globl	f
	.type	f,@function
f:                                      # @f
	.result 	i32
# BB#0:                                 # %entry
	i32.const	$push0=, 65535
	return  	$pop0
func_end0:
	.size	f, func_end0-f

	.globl	g
	.type	g,@function
g:                                      # @g
	.result 	i64
# BB#0:                                 # %entry
	i64.const	$push0=, 65535
	return  	$pop0
func_end1:
	.size	g, func_end1-g

	.globl	main
	.type	main,@function
main:                                   # @main
	.result 	i32
# BB#0:                                 # %entry
	i32.const	$push0=, 0
	call    	exit, $pop0
	unreachable
func_end2:
	.size	main, func_end2-main


	.ident	"clang version 3.8.0 "
	.section	".note.GNU-stack","",@progbits