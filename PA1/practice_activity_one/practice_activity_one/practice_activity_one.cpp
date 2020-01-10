// practice_activity_one.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm> 
#include <time.h>
using namespace std;

class Music {
public:
	unsigned int year;
	string artist_name;
	string music_id;
	Music() {
		year = 0;
	}

	Music(unsigned int new_year, string new_artist_name, string new_music_id) {
		year = new_year;
		artist_name = new_artist_name;
		music_id = new_music_id;
	}

	bool operator==(const Music& compare_music) {
		if (year == compare_music.year && artist_name == compare_music.artist_name && year == compare_music.year) {
			return true;
		}
		else {
			return false;
		}
	}

	string get_artist() {
		return this->artist_name;
	}

};

class Song : public Music{
public:
	string genre;
	string song_name;
	unsigned int song_length;

	Song() {
		song_length = 0;
	}

	Song(string new_genre, string new_song_name, unsigned int new_song_length, Music new_music) : genre(new_genre), song_name(new_song_name), song_length(new_song_length), Music(new_music) {}

	bool operator==(const Song& compare_song) {
		if (song_length == compare_song.song_length && song_name == compare_song.song_name && genre == compare_song.genre) {
			Music compare_music = static_cast<Music>(compare_song);
			return compare_music == static_cast<Music>(*this);
		}
		else {
			return false;
		}
	}
};

class Playlist {
	

public:
	friend Playlist operator+(const Playlist& playlist_one, const Playlist& playlist_two);
	vector<Song> my_playlist;

	bool insert_song(Song& song_info) {
		string artist = song_info.get_artist();
		int artist_count = 0;
		bool can_insert = true;
		for (Song song : my_playlist){
			if (song == song_info) {
				can_insert = false;
			}
			if (artist == song.get_artist()) {
				++artist_count;
			}
		}
		can_insert == can_insert && (artist_count > 3);
		if (can_insert) {
			my_playlist.push_back(song_info);
		}
		return can_insert;
	}


	Playlist shuffle_songs() {
		Playlist shuffled_playlist;
		vector<int> randomized;
		for (int i = 0; i < my_playlist.size(); ++i) {
			randomized.push_back(i);
		}
		random_shuffle(randomized.begin(), randomized.end());
		for (int i = 0; i < randomized.size(); ++i) {
			shuffled_playlist.insert_song(my_playlist[i]);
		}
		return shuffled_playlist;
	}

};

Playlist operator+(Playlist& playlist_one, Playlist& playlist_two) {
	Playlist combine_playlist;
	for(int i = 0; i < playlist_one.my_playlist.size(); ++i) {
		combine_playlist.insert_song(playlist_one.my_playlist[i]);
	}
	for (int i = 0; i < playlist_two.my_playlist.size(); ++i) {
		combine_playlist.insert_song(playlist_two.my_playlist[i]);
	}

	return combine_playlist;
}




int main()
{
	srand(time(0));

    std::cout << "Hello World!\n";
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
