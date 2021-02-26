# coverage: 
    coverage can be found in the cmake-build-debug/CmakeFiles/<lib_name>.dir/out directories
        coverage statistics:
            stack: 75% 
            rpn: 88%
            infix: 81%
            
# how to build
    idk use the cmake, executable names are:
     test_stack : tests everything (I'm lazy with names)
     SADS_1 : rpnc executable
     run_infix: runs the infix calculator

     Since I'm using Clion, executables are built out of cmake-build-debug directory. If this is too complex 
     let me know and I will use Cmake properly next time.
     run make in the root directory to run the fuzzer.

# fuzzer
    To use the fuzzer, run make ( I couldn't get it to work with Cmake), I ran it
    and got no crashes. The results are in the afl_findings directory. (there is a screenshot there as well of my terminal's output)
     
    