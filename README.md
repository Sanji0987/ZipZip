# Zipper

File compression tool in C. Reads a file, builds a frequency table of 16-bit values using a hash table (Knuth's multiplicative hash), and will eventually use that to compress the data.

Still early — right now it builds the frequency table and verifies lookups. Compression/decompression not implemented yet.

## Building

```
make
```

Debug build with sanitizers:

```
make DEBUG=1
```

## Usage

```
./main <file>
```
