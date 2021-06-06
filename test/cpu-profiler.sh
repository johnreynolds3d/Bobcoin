# run executable with CPUPROFILE environment var set
#LD_PRELOAD=/usr/local/lib/libprofiler.so CPUPROFILE=test/test.prof ./bin/bobcoin
CPUPROFILE=test/test.prof ./bin/bobcoin

# run pprof and view results in web browser
pprof -http=localhost:8000 ./bin/bobcoin test/test.prof

# run pprof to output one line per procedure 
#pprof --text ./bin/bobcoin test/test.prof

# run pprof to get graphical output
#pprof -gv ./bin/bobcoin test/test.prof

# generate PDF report with previous graphical output
#pprof --pdf ./bin/bobcoin test/test.prof > test/test.profile.pdf
