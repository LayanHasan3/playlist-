#include <iostream>
#include <string>

using namespace std;

// Structure for a song node
struct Song {
    string title;
    string artist;
    Song* next;
    Song* prev;
};

// Head, Tail, and Current song pointers
Song* head = nullptr;
Song* tail = nullptr;
Song* current = nullptr;

// Function to add a song to the playlist
void addSong(string title, string artist) {
    Song* newSong = new Song();
    newSong->title = title;
    newSong->artist = artist;
    newSong->next = nullptr;
    newSong->prev = tail;

    if (head == nullptr) { // If playlist is empty
        head = tail = current = newSong;
    } else { // Add at the end
        tail->next = newSong;
        tail = newSong;
    }
    cout << "Added: " << title << " by " << artist << endl;
}

// Function to remove a song by title
void removeSong(string title) {
    Song* temp = head;

    while (temp) {
        if (temp->title == title) {
            if (temp->prev) 
                temp->prev->next = temp->next;
            else 
                head = temp->next; // Update head if deleting the first node

            if (temp->next) 
                temp->next->prev = temp->prev;
            else 
                tail = temp->prev; // Update tail if deleting the last node

            if (current == temp) 
                current = (temp->next) ? temp->next : head; // Move to next or restart

            delete temp;
            cout << "Removed: " << title << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Song not found: " << title << endl;
}

// Function to play the next song
void playNext() {
    if (!current) {
        cout << "Playlist is empty." << endl;
        return;
    }
    current = (current->next) ? current->next : head; // Loop back to first song if at end
    cout << "Now playing: " << current->title << " by " << current->artist << endl;
}

// Function to play the previous song
void playPrevious() {
    if (!current) {
        cout << "Playlist is empty." << endl;
        return;
    }
    current = (current->prev) ? current->prev : tail; // Loop back to last song if at start
    cout << "Now playing: " << current->title << " by " << current->artist << endl;
}

// Function to display the playlist
void displayPlaylist() {
    if (!head) {
        cout << "Playlist is empty." << endl;
        return;
    }

    cout << "\nPlaylist:" << endl;
    Song* temp = head;
    while (temp) {
        cout << "- " << temp->title << " by " << temp->artist << endl;
        temp = temp->next;
    }
}

// Function to show menu and take user input
void showMenu() {
    int choice;
    string title, artist;

    while (true) {
        cout << "\n🎵 Music Playlist Manager 🎵\n";
        cout << "1. Add Song\n";
        cout << "2. Remove Song\n";
        cout << "3. Play Next\n";
        cout << "4. Play Previous\n";
        cout << "5. Show Playlist\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // Ignore newline character after input

        switch (choice) {
            case 1:
                cout << "Enter song title: ";
                getline(cin, title);
                cout << "Enter artist name: ";
                getline(cin, artist);
                addSong(title, artist);
                break;

            case 2:
                cout << "Enter song title to remove: ";
                getline(cin, title);
                removeSong(title);
                break;

            case 3:
                playNext();
                break;

            case 4:
                playPrevious();
                break;

            case 5:
                displayPlaylist();
                break;

            case 6:
                cout << "Exiting... 🎧" << endl;
                return;

            default:
                cout << "Invalid choice! Please enter a number from 1 to 6." << endl;
        }
    }
}

// Main function
int main() 
{
    showMenu();
    return 0;
}