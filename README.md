# magnet2torrent

`magnet2torrent` is a C++ program that converts a magnet link to a `.torrent` file using the [libtorrent](https://www.libtorrent.org/) library. This tool is designed to help users create torrent files from magnet URIs, which can be useful for sharing and managing torrents.

## Features

- Converts a magnet link to a `.torrent` file.
- Uses the libtorrent library for torrent management.
- Allows you to specify the output filename for the generated `.torrent` file.

## Usage

To use the program, you need to provide the magnet link and the desired output filename as command-line arguments:


Example:

```sh
./magnet2torrent "magnet:?xt=urn:btih:..." "output.torrent"
```

## Building on Arch Linux

To compile and build the `magnet2torrent` program on Arch Linux, follow these steps:

1. **Install Dependencies:**

   ```sh
   sudo pacman -S libtorrent-rasterbar libtorrent-rasterbar boost boost-libs gcc
   ```

2. **Compile the Program:**

   ```sh
   g++ -o magnet2torrent main.cpp -lcurl -ltorrent-rasterbar -lstdc++fs
   ```

## Code Overview

The main functionality is implemented in the `main.cpp` file, which includes:

- **`createTorrentFile` Function:** Converts a magnet link to a `.torrent` file. It initializes a libtorrent session, parses the magnet link, retrieves the torrent metadata, and writes the torrent file to disk.
  
- **`main` Function:** Handles command-line arguments and calls the `createTorrentFile` function.

## Dependencies

- [libtorrent-rasterbar](https://www.libtorrent.org/)
- [Boost](https://www.boost.org/)
- [libcurl](https://curl.se/libcurl/)
