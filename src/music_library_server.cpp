/**
 * @file
 *
 * This is the main server process.  When it starts it listens for clients.  It then
 * accepts remote commands for modifying/viewing the music database.
 *
 */

#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <memory>
#include <mutex>

#include "MusicLibrary.h"
#include "JsonMusicLibraryApi.h"

#include <C:\Users\Mozer\Documents\School\FourthYear\CPEN333\Library\library\include\cpen333\process\socket.h>

/**
 * Main thread function for handling communication with a single remote
 * client.
 *
 * @param lib shared library
 * @param api communication interface layer
 * @param id client id for printing messages to the console
 */
void service(MusicLibrary &lib, MusicLibraryApi &&api, int id) {

  //=========================================================
  // TODO: Implement thread safety
  //=========================================================

  // Need a mutex to protect the print statements and access to library
  static std::mutex mutex; 
  
  // PROTECT THIS
  mutex.lock();
  std::cout << "Client " << id << " connected" << std::endl;
  mutex.unlock();
  
  // receive message
  std::unique_ptr<Message> msg = api.recvMessage();

  // continue while we don't have an error
  while (msg != nullptr) {

    // react and respond to message
    MessageType type = msg->type();
    switch (type) {
      case MessageType::ADD: {
        // process "add" message
        // get reference to ADD
        AddMessage &add = (AddMessage &) (*msg);
		
		mutex.lock();
        std::cout << "Client " << id << " adding song: " << add.song << std::endl;

        // add song to library
        bool success = false;
        success = lib.add(add.song);
		mutex.unlock();
		
        // send response
        if (success) {
          api.sendMessage(AddResponseMessage(add, MESSAGE_STATUS_OK));
        } else {
          api.sendMessage(AddResponseMessage(add,
            MESSAGE_STATUS_ERROR,
            "Song already exists in database"));
        }
        break;
      }
      case MessageType::REMOVE: {
        //====================================================
        // TODO: Implement "remove" functionality
        //====================================================
		  std::cout << "STARTING REMOVAL" << std::endl;

		// get reference to REMOVE
		RemoveMessage &remove = (RemoveMessage &) (*msg);
		
		std::cout << "CREATED REMOVE MESSAGE" << std::endl;

		mutex.lock();
		std::cout << "Client " << id << "removing song: " << remove.song << std::endl;
		
		// remove song from library
		bool success = false;
		success = lib.remove(remove.song);
		mutex.unlock();
		
		// send response
		if(success){
			api.sendMessage(RemoveResponseMessage(remove, MESSAGE_STATUS_OK));
		}
		
		else{
			api.sendMessage(RemoveResponseMessage(remove, 
												  MESSAGE_STATUS_ERROR,
												  "Song doesn't exist"));
			
		}

        break;
      }
      case MessageType::SEARCH: {
        // process "search" message
        // get reference to SEARCH
        SearchMessage &search = (SearchMessage &) (*msg);

		mutex.lock();
        std::cout << "Client " << id << " searching for: "
                    << search.artist_regex << " - " << search.title_regex << std::endl;

        // search library
        std::vector<Song> results;
        results = lib.find(search.artist_regex, search.title_regex);

        // send response
        api.sendMessage(SearchResponseMessage(search, results, MESSAGE_STATUS_OK));

		mutex.unlock();
		
        break;
      }
      case MessageType::GOODBYE: {
        // process "goodbye" message
		mutex.lock();
        std::cout << "Client " << id << " closing" << std::endl;
		mutex.unlock();
        return;
      }
      default: {
		mutex.lock();
        std::cout << "Client " << id << " sent invalid message" << std::endl;
		mutex.unlock();
      }
    }

    // receive next message
    msg = api.recvMessage();
  }
}

/**
 * Load songs from a JSON file and add them to the music library
 * @param lib music library
 * @param filename file to load
 */
void load_songs(MusicLibrary &lib, const std::string& filename) {

  // parse from file stream
  std::ifstream fin(filename);
  if (fin.is_open()) {
    JSON j;
    fin >> j;
    std::vector<Song> songs = JsonConverter::parseSongs(j);
    lib.add(songs);
  } else {
    std::cerr << "Failed to open file: " << filename << std::endl;
  }

}

int main() {

  // load  data
  std::vector<std::string> filenames = {
      "data/billboard_hot_100.json",
      "data/billboard_greatest_hot_100.json",
      "data/billboard_adult_contemporary.json",
      "data/billboard_adult_pop.json",
      "data/billboard_alternative.json",
      "data/billboard_country.json",
      "data/billboard_electronic.json",
      "data/billboard_jazz.json",
      "data/billboard_r&b.json",
      "data/billboard_rap.json",
      "data/billboard_rock.json",
  };

  MusicLibrary lib;       // main shared music library

  // load music library files
  for (const auto &filename : filenames) {
    load_songs(lib, filename);
  }

  // start server
  cpen333::process::socket_server server(MUSIC_LIBRARY_SERVER_PORT);
  server.open();
  std::cout << "Server started on port " << server.port() << std::endl;

  //===============================================================
  // TODO: Modify to allow multiple client-server connections
  //     Loop:
  //       - 'Accept' a socket client
  //       - Create an API wrapper around the socket
  //       - Send the API wrapper to the service(...) function
  //         to run in a new detached thread
  //===============================================================
  
  int count = 0;
  // Accepts clients until we fail
  while(true){
	  cpen333::process::socket client;
	  if(server.accept(client)) {
		  
		// create API handler
		JsonMusicLibraryApi api(std::move(client));
		// Create each service handler function in a separate thread
		std::thread thread(service, std::ref(lib), std::move(api), count);
		// Detach the thread to run on its own
		thread.detach();
		count++;
	  }
  }

  // close server
  server.close();

  return 0;
}