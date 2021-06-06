# run executable with HEAPPROFILE environment var set
HEAPPROFILE=test/heapprof HEAPCHECK=draconian ./bin/bobcoin

# run pprof and view results in a web browser
pprof -http=localhost:8000 ./bin/bobcoin test/heapprof.0001.heap

# run pprof to output one line per procedure 
#pprof --text ./bin/bobcoin test/heapprof.0001.heap 

# run pprof to get graphical output
#pprof -gv ./bin/bobcoin test/heapprof.0001.heap

# generate PDF report with previous graphical output
pprof --pdf ./bin/bobcoin test/heapprof.0001.heap > test/heapprof.0001.heap.pdf 
