#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <memory>
#include <libtorrent/session.hpp>
#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/torrent_info.hpp>
#include <libtorrent/create_torrent.hpp>
#include <libtorrent/bencode.hpp>
#include <libtorrent/magnet_uri.hpp>

namespace lt = libtorrent;

void createTorrentFile(const std::string& magnetLink, const std::string& outputFilename) {
    try {
        // Set up session
        lt::settings_pack spack;
        spack.set_bool(lt::settings_pack::enable_dht, false);
        spack.set_bool(lt::settings_pack::enable_upnp, false);
        spack.set_bool(lt::settings_pack::enable_natpmp, false);

        // Create session with the settings
        lt::session ses(spack);

        // Parse magnet link
        lt::add_torrent_params atp = lt::parse_magnet_uri(magnetLink);
        atp.save_path = "."; // Save in the current directory

        // Add torrent to session
        lt::torrent_handle th = ses.add_torrent(atp);

        // Wait for torrent metadata to be downloaded
        for (int i = 0; i < 60; ++i) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            lt::torrent_status st = th.status();
            if (st.has_metadata) {
                // Metadata is available, proceed with creating the .torrent file
                std::shared_ptr<const lt::torrent_info> ti = th.torrent_file();
                if (ti->is_valid()) {
                    lt::create_torrent ct(*ti);
                    std::ofstream outFile(outputFilename, std::ios::binary);
                    if (!outFile.is_open()) {
                        throw std::runtime_error("Unable to open file for writing: " + outputFilename);
                    }
                    lt::bencode(std::ostream_iterator<char>(outFile), ct.generate());
                    std::cout << "Created .torrent file: " << outputFilename << std::endl;
                } else {
                    std::cerr << "Invalid torrent info" << std::endl;
                }
                return;
            }
        }

        std::cerr << "Failed to retrieve metadata for magnet link: " << magnetLink << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <magnet-url> <output-filename>" << std::endl;
        return 1;
    }

    std::string magnetLink = argv[1];
    std::string outputFilename = argv[2];

    createTorrentFile(magnetLink, outputFilename);

    return 0;
}
