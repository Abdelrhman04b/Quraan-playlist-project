#include <iostream>
#include <string>
#include <fstream>
#include "Playlist.cpp"
using namespace std;
#pragma once

struct PLMnode
{
    Playlist Data;
    PLMnode *next; // Creating pointer to (The next node in the list)
    PLMnode *prev; // Creating pointer to (The prev node in the list)
    PLMnode() : Data(), next(nullptr), prev(nullptr) {};
    PLMnode(const Playlist Element) : Data(Element), next(nullptr), prev(nullptr) {};
};

// The playlistmanger class include a linked list of playlists
class PlaylistManager
{
private:
    PLMnode *head;
    PLMnode *tail;
    unsigned int NumOfPlaylists = 0;
    // Helper functions for the linked list
    bool IsEmpty() { return head == nullptr; } // Checks if the linked list is empty

public:
    // Constructor
    PlaylistManager();
    // Destructor
    ~PlaylistManager();
    // 1.Insert at begin
    void InsertBegin(const Playlist &Element);
    // 2.Insert at end
    void InsertEnd(const Playlist &Element);
    // 3.Insert at index
    void InsertIndex(const Playlist &Element, int Index);
    // 4.Delete at begin
    void DeleteBegin();
    // 5.Delete at end
    void DeleteEnd();
    // 6.Delete at index
    void DeleteIndex(int Index);
    // 7.Display playlists
    void Display();
    // 8.Get first playlist
    Playlist &GetHead();
    // 9.Get last playlist
    Playlist &GetTail();
    // 10.Get index playlist
    Playlist &GetIndex(int Index);
    // 11.Get number of playlists
    int GetNumOfLists();
    // 12.Display Index
    string DisplayIndex(int Index);
    // 13.Get name playlist
    Playlist GetByName(string name);
};

// Constructor
PlaylistManager::PlaylistManager() : head(nullptr), tail(nullptr) {};
// Destructor
PlaylistManager::~PlaylistManager()
{
    PLMnode *Current;
    PLMnode *NToD = head;
    while (NToD != nullptr)
    {
        Current = NToD->next;
        delete NToD;
        NToD = Current;
    }
}

void PlaylistManager::InsertBegin(const Playlist &Element)
{
    PLMnode *newPlaylist = new PLMnode(Element);
    if (IsEmpty())
    {
        head = newPlaylist;
        tail = newPlaylist;
    }
    else
    {
        newPlaylist->next = head;
        head->prev = newPlaylist;
        head = newPlaylist;
    }
    NumOfPlaylists++;
}

void PlaylistManager::InsertEnd(const Playlist &Element)
{
    if (IsEmpty())
        InsertBegin(Element);
    else
    {
        PLMnode *newPlaylist = new PLMnode(Element);
        newPlaylist->prev = tail;
        tail->next = newPlaylist;
        tail = newPlaylist;
        NumOfPlaylists++;
    }
}

void PlaylistManager::InsertIndex(const Playlist &Element, int Index)
{

    if (Index < 1)
    {
        cout << "Invalid index!!\n";
        return;
    }
    if (Index == 1)
    {
        InsertBegin(Element);
        return;
    }
    PLMnode *Current = head;
    for (int i = 1; Current != nullptr && i < Index - 1; i++)
    {
        Current = Current->next;
    }
    if (Current == nullptr)
    {
        cout << "Index out of range!!\n";
        return;
    }
    if (Current->next == nullptr)
    {
        InsertEnd(Element);
        return;
    }
    PLMnode *newPlaylist = new PLMnode(Element);
    newPlaylist->next = Current->next;
    newPlaylist->prev = Current;
    Current->next->prev = newPlaylist;
    Current->next = newPlaylist;
    NumOfPlaylists++;
}

void PlaylistManager::DeleteBegin()
{

    if (IsEmpty())
    {
        cout << "The list is already empty!!\n";
        return;
    }
    if (head->next == nullptr) // Checks if there is only one node
    {
        delete head;
        head = tail = nullptr;
    }
    else
    {
        PLMnode *Temp = head;
        head = head->next;
        head->prev = nullptr;
        delete Temp;
    }
    NumOfPlaylists--;
}

void PlaylistManager::DeleteEnd()
{

    if (IsEmpty())
    {
        cout << "The list is already empty!!\n";
        return;
    }
    if (head->next == nullptr)
    {
        delete head;
        head = tail = nullptr;
    }
    else
    {
        PLMnode *NToD = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete NToD;
    }
    NumOfPlaylists--;
}

void PlaylistManager::DeleteIndex(int Index)
{
    if (Index < 1)
    {
        cout << "Index invalid!!\n";
        return;
    }
    if (IsEmpty())
    {
        cout << "There is no playlists to delete!!\n";
        return;
    }
    PLMnode *Current = head;
    if (Index == 1)
    {
        DeleteBegin();
    }
    else
    {
        for (int i = 1; Current != nullptr && i < Index; i++)
        {
            Current = Current->next;
        }
        if (Current == nullptr)
        {
            cout << "Index out of bounds!!\n";
            return;
        }
        if (Current->next == nullptr)
        {
            DeleteEnd();
            return;
        }
        Current->next->prev = Current->prev;
        Current->prev->next = Current->next;
        delete Current;
        NumOfPlaylists--;
    }
}

void PlaylistManager::Display()
{
    if (head == nullptr)
        cout << "There is no playlists in the list!!\n";
    else
    {
        PLMnode *Current = head;
        for (int i = 1; Current != nullptr; i++)
        {
            cout << i << ". " << Current->Data.GetName() << endl;
            Current = Current->next;
        }
    }
}

Playlist &PlaylistManager::GetHead()
{
    return head->Data;
}

Playlist &PlaylistManager::GetTail()
{
    return tail->Data;
}

Playlist &PlaylistManager::GetIndex(int Index)
{
    if (IsEmpty()) // Checks if the list is empty
    {
        cout << "There is no data in the list!!\n";
        static PLMnode defaultPLMnode;
        return defaultPLMnode.Data;
    }
    if (Index < 1) // Checks if index is out of range
    {
        cout << "Invalid index!!\n";
        // return;
    }
    else
    {
        PLMnode *Current = head;
        for (int i = 1; Current != nullptr && i < Index; i++)
        {
            Current = Current->next;
        }
        if (Current == nullptr) // Checks if index is out of range
        {
            cout << "Index out of range!!\n";
        }
        else
            return Current->Data;
    }
    static PLMnode defaultPLMnode;
    return defaultPLMnode.Data;
}

int PlaylistManager::GetNumOfLists() { return NumOfPlaylists; }

string PlaylistManager::DisplayIndex(int Index)
{
    if (IsEmpty()) // Checks if the list is empty
    {
        cout << "There is no data in the list!!\n";
    }
    else
    {
        if (Index < 1) // Checks if index is out of range
        {
            cout << "Invalid index!!\n";
        }
        else
        {
            PLMnode *Current = head;
            for (int i = 1; Current != nullptr && i < Index; i++)
            {
                Current = Current->next;
            }
            if (Current == nullptr) // Checks if index is out of range
            {
                cout << "Index out of range!!\n";
            }
            else
                return Current->Data.GetName();
        }
    }
    return 0;
}

Playlist PlaylistManager::GetByName(string name)
{
    if (IsEmpty()) // Checks if the list is empty
    {
        cout << "There is no data in the list!!\n";
    }
    else
    {
        PLMnode *Current = head;
        while (Current != nullptr)
        {
            if (Current->Data.GetName() == name)
            {
                return Current->Data;
            }
            Current = Current->next;
        }
        cout << "There is no playlist with the name you entered!!\n";
    }
    return Playlist();
}
