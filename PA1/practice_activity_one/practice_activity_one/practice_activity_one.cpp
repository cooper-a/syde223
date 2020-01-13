#include <iostream>
#include <string>
#include <vector>
#include <time.h>

//Custom assertion for easier testing
#define ASSERT(condition) if(!(condition)) return false

using namespace std;

int MAX_ARTIST_COUNT = 3;

class Music {
	friend class TestMusic;
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
		return artist_name;
	}
};

class Song : public Music{
	friend class TestMusic;
public:
	string genre;
	string song_name;
	unsigned int song_length;

	Song() : song_length(0) {
	}

	Song(string new_genre, string new_song_name, unsigned int new_song_length, Music new_music) : 
        genre(new_genre), song_name(new_song_name), song_length(new_song_length), Music(new_music) {
    }

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
    friend class TestMusic;
	friend Playlist operator+(const Playlist& playlist_one, const Playlist& playlist_two);
public:
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

		can_insert = can_insert && (artist_count < MAX_ARTIST_COUNT);
		if (can_insert) {
			my_playlist.push_back(song_info);
		}
		return can_insert;
	}

	Playlist shuffle_songs() {
		Playlist shuffled_playlist;
		vector<Song> copy_playlist = my_playlist;

		for (int i = my_playlist.size() - 1; i > 0; i--) {
			int rand_num = (rand() % (i + 1));
            auto temp = my_playlist[rand_num];
            my_playlist[rand_num] = my_playlist[i];
            my_playlist[i] = temp;
		}

		shuffled_playlist.my_playlist = copy_playlist;
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

class TestMusic {
public:
	bool testMusicGetArtist();
	bool testMusicDefaultConstructor();
	bool testMusicParametricConstructor();
	bool testMusicOperatorEquals();
	bool testSongDefaultConstructor();
	bool testSongParametricConstructor();
	bool testSongOperatorEquals();
	bool testPlaylistInsertSong();
	bool testPlaylistShuffleSongs();
    bool testPlaylistOperatorPlus();

	void run();
};

bool TestMusic::testMusicDefaultConstructor() {
    //Test default values of default constructor
    Music m;
    ASSERT(m.artist_name == "");
    ASSERT(m.music_id == "");
    ASSERT(m.year == 0);
    return true;
}

bool TestMusic::testMusicParametricConstructor() {
    //Test parametric constructor adds values
    Music m = Music(2017, "BTS", "AGoodSong");
    ASSERT(m.artist_name == "BTS");
    ASSERT(m.music_id == "AGoodSong");
    ASSERT(m.year == 2017);
    return true;
}

bool TestMusic::testMusicGetArtist() {
    //Test get_artist() returns artist
    Music m = Music(2017, "BTS", "AGoodSong");
    ASSERT(m.get_artist() == "BTS");
    return true;
}

bool TestMusic::testMusicOperatorEquals() {
    //Test operator== returns correct value for empty comparisons and actual comparisons
    Music m1 = Music(2017, "BTS", "AGoodSong");
    Music m2 = Music(2017, "BTS", "AGoodSong");
    ASSERT(m1 == m2);
    Music m3;
    Music m4;
    ASSERT(m3 == m4);
    return true;
}

bool TestMusic::testSongDefaultConstructor() {
    Music m;
    Song s;
    ASSERT(static_cast<Music>(s) == m);
    ASSERT(s.genre == "");
    ASSERT(s.song_length == 0);
    ASSERT(s.song_name == "");
    return true;
}

bool TestMusic::testSongParametricConstructor() {
    Music m = Music(2017, "BTS", "AGoodSong");
    Song s = Song("Kpop", "DNA", 223, m);
    ASSERT(static_cast<Music>(s) == m);
    ASSERT(s.genre == "Kpop");
    ASSERT(s.song_name == "DNA");
    ASSERT(s.song_length == 223);
    return true;
}

bool TestMusic::testSongOperatorEquals() {
    Song s1 = Song("Kpop", "DNA", 223, Music(2017, "BTS", "AGoodSong"));
    Song s2 = Song("Kpop", "DNA", 223, Music(2017, "BTS", "AGoodSong"));
    ASSERT(s1 == s2);
    Song s3;
    Song s4;
    ASSERT(s3 == s4);
    return true;
}

bool TestMusic::testPlaylistInsertSong() {
    Playlist p;
    Song s1 = Song("Kpop", "DNA", 223, Music(2017, "BTS", "AGoodSong"));
    Song s2 = Song("Kpop", "Spring Day", 274, Music(2016, "BTS", "ADifferentGoodSong"));
    Song s3 = Song("Kpop", "Blood, Sweat, and Tears", 217, Music(2016, "BTS", "AReallyGoodSong"));
    Song s4 = Song("Kpop", "Boy With Luv", 230, Music(2019, "BTS", "BTSSong#???+3"));
    //test insert_song
    ASSERT(p.insert_song(s1));
    ASSERT(p.my_playlist.size() == 1);
    ASSERT(p.my_playlist[0] == s1);
    ASSERT(p.insert_song(s2));
    ASSERT(p.my_playlist.size() == 2);
    //test inserting a duplicate song
    ASSERT(!p.insert_song(s1));
    p.insert_song(s3);
    //test inserting a 4th song from same artist
    ASSERT(!p.insert_song(s4));
    return true;
}

bool TestMusic::testPlaylistShuffleSongs() {
    Playlist p;
    vector<Song> songs;
    songs.push_back(Song("Kpop", "DNA", 223, Music(2017, "BTS", "AGoodSong")));
    songs.push_back(Song("Kpop", "Spring Day", 274, Music(2016, "BTS", "ADifferentGoodSong")));
    songs.push_back(Song("Kpop", "Blood, Sweat, and Tears", 217, Music(2016, "BTS", "AReallyGoodSong")));
    for(auto& s : songs) {
        p.insert_song(s);
    }

    Playlist shuffled = p.shuffle_songs();
    ASSERT(shuffled.my_playlist.size() == p.my_playlist.size());

    //Test that all songs in the original playlist are in the shuffled playlist
    for(auto& pSong : p.my_playlist) {
        bool found = false;
        for(auto& shuffledSong : shuffled.my_playlist) {
            if (pSong == shuffledSong) found = true;
        }
        ASSERT(found);
    }
    return true;
}

bool TestMusic::testPlaylistOperatorPlus() {
    //create two playlists with 
    Playlist p1;
    vector<Song> songs1;
    songs1.push_back(Song("Kpop", "DNA", 223, Music(2017, "BTS", "AGoodSong")));
    songs1.push_back(Song("Kpop", "Spring Day", 274, Music(2016, "BTS", "ADifferentGoodSong")));
    songs1.push_back(Song("Kpop", "Blood, Sweat, and Tears", 217, Music(2016, "BTS", "AReallyGoodSong")));
    for(auto& s : songs1) p1.insert_song(s);

    Playlist p2;
    vector<Song> songs2;
    songs2.push_back(Song("Kpop", "DDU-DU DDU-DU", 261, Music(2016, "BlackPink", "WhatIsASongID")));
    songs2.push_back(Song("Kpop", "Gangnam Style", 219, Music(2012, "PSY", "SongIdHere")));
    songs2.push_back(Song("Kpop", "SOLO", 169, Music(2018, "JENNIE", "IdOfSong")));
    for(auto& s : songs2) p2.insert_song(s);
    
    //test operator+ creates a new playlist
    Playlist combined = p1 + p2;
    ASSERT(combined.my_playlist.size() == (p1.my_playlist.size() + p2.my_playlist.size()));
    ASSERT(combined.my_playlist[p1.my_playlist.size()] == p2.my_playlist[0]);
    Playlist empty;
    Playlist plusEmpty = p1 + empty;
    ASSERT(plusEmpty.my_playlist.size() == p1.my_playlist.size());
    
    return true;
}

void TestMusic::run() {
    // run all tests
    int failCount = 0;
    if (!testMusicGetArtist()) {
        cout << "testMusicGetArtist failed" << endl;
        failCount++;
    }
    if (!testMusicDefaultConstructor()) {
        cout << "testMusicDefaultConstructor failed" << endl;
        failCount++;
    }
    if (!testMusicParametricConstructor()) {
        cout << "testMusicParametricConstructor failed" << endl;
        failCount++;
    }
    if (!testMusicOperatorEquals()) {
        cout << "testMusicOperatorEquals failed" << endl;
        failCount++;
    }
    if (!testSongDefaultConstructor()) {
        cout << "testSongDefaultConstructor failed" << endl;
        failCount++;
    }
    if (!testSongParametricConstructor()) {
        cout << "testSongParametricConstructor failed" << endl;
        failCount++;
    }
    if (!testSongOperatorEquals()) {
        cout << "testSongOperatorEquals failed" << endl;
        failCount++;
    }
    if (!testPlaylistInsertSong()) {
        cout << "testPlaylistInsertSong failed" << endl;
        failCount++;
    }
    if (!testPlaylistShuffleSongs()) {
        cout << "testPlaylistShuffleSongs failed" << endl;
        failCount++;
    }
    if (!testPlaylistOperatorPlus()) {
        cout << "testPlaylistOperatorPlus failed" << endl;
        failCount++;
    }
    if (failCount) {
        cout << "Fail count: " << failCount << endl;
    } else {
        cout << "All tests passed!" << endl;
    }
}

int main()
{
	srand(time(0));
	TestMusic tester;
    tester.run();
    return 0;
}
