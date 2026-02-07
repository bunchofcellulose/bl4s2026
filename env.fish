alias tmake="rm test.root; hadd test.root output0_t0.root output0_t1.root output0_t2.root output0_t3.root"
alias clean="rm -rf output*"
alias g4make="cmake ..; and make -j4"
alias run="g4make; and QT_QPA_PLATFORM=xcb ./main"
alias troot="root --web=off test.root"

function runmt --description "Build, Run, and Save"
    set file $argv[1]

    if test -z "$file"
        echo "Please provide a name for the file. Usage: runmt <file_name>"
        return 1
    end

    g4make
    if test $status -ne 0; return 1; end
    ./main run.mac
    if test $status -ne 0; cd ..; return 1; end
    tmake
    mv -i test.root "../root/$file" 
    clean
end

echo "Geant4 Project Environment Loaded"