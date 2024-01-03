
#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>
#include <90s/orm/json.hpp>

using namespace s90::orm;

struct post : public with_orm {
    WITH_ID;
    int id;
    std::string author;
    std::string text;
    optional<datetime> created_at;

    mapper get_orm() {
        return {
            {"id", id},
            {"author", author},
            {"text", text},
            {"created_at", created_at}
        };
    }
};

struct thread : public with_orm {
    WITH_ID;

    int id;
    std::string name;
    std::vector<post> posts;

    mapper get_orm() {
        return {
            {"id", id},
            {"name", name},
            {"posts", posts}
        };
    }
};

/// @brief Run as bin/coder file_name, use -p flag to force printing the read JSON
/// @param argc number of args
/// @param argv args
/// @return status
int main(int argc, const char **argv) {
    std::string target_file = "resources/threads.json";
    bool do_print = false;
    for(int i = 0; i < argc; i++) {
        if(argv[i] == std::string("-p")) do_print = true;
        else if(i >= 1) target_file = argv[i];
    }
    std::ifstream ifs(target_file);
    if(ifs) {
        json_decoder dec;

        std::stringstream ss;
        ss << ifs.rdbuf();
        ifs.close();

        auto start = std::chrono::high_resolution_clock::now();
        auto result = dec.decode<std::vector<thread>>(ss);
        auto end = std::chrono::high_resolution_clock::now();
        if(result) {
            auto& threads = *result;

            if(do_print) {
                for(auto t : threads) {
                    std::cout << "Thread: " << t.name << std::endl << std::endl;
                    for(auto& p : t.posts) {
                        std::cout << "#" << p.id << " | Author: " << p.author << std::endl;
                        if(p.created_at) {
                            std::cout << "Created at: " << p.created_at->ymdhis() << std::endl;
                        }
                        std::cout << p.text << std::endl << std::endl;
                    }
                }
            }

            // let's create a new JSON!
            threads.emplace_back(thread {
                .id = 3,
                .name = "90's",
                .posts = {
                    post {
                        .id = 4,
                        .author = "diznq",
                        .text = "I think 80's is a great project!",
                        .created_at = datetime()
                    }
                }
            });

            std::cout << "Decoding took " << std::chrono::duration<double>(end - start).count() << " seconds" << std::endl;

            json_encoder enc;
            start = std::chrono::high_resolution_clock::now();
            auto encoded = enc.encode(threads);
            end = std::chrono::high_resolution_clock::now();
            
            std::cout << "Encoding took " << std::chrono::duration<double>(end - start).count() << " seconds" << std::endl;
            
            std::ofstream ofs("resources/threads_new.json", std::ios::binary);
            if(ofs) {
                ofs << encoded;
                ofs.close();
            }
        } else {
            std::cerr << result.error() << std::endl;
        }
    }
}