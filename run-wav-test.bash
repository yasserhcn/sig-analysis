echo "compiling wav tests..."
g++ test/openWavTest.cpp test/runWavTest.cpp src/files/wav/openWav.cpp \
    -I src/include -o build/wavTest.out
echo "compilation complete"

./build/wavTest.out