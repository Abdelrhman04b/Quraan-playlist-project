#include "Playlist.cpp"
#include "Surah.cpp"
#include "PlaylistManager.cpp"
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <mmsystem.h>
#include <tchar.h>
using namespace std;
#pragma comment(lib, "winmm.lib")

void DisplayPlaylistsShurahs(PlaylistManager &Manager)
{
    for (int i = 1; i <= Manager.GetNumOfLists(); i++)
    {
        cout << "\n==================\n";
        cout << Manager.DisplayIndex(i) << " playlist:" << endl;
        Manager.GetIndex(i).Display();
        cout << "==================\n";
    }
}

int ReadNumberInRange(int From, int To, string Message)
{
    int Number;
    do
    {
        cout << "Between(" << From << "," << To << ") " << Message;
        cin >> Number;
    } while (Number < From || Number > To);
    return Number;
}

string ReadString(string message)
{
    string Order;
    cout << message;
    cin >> Order;
    return Order;
}

void PrintList(int &Number)
{
    cout << "========================================================================================================================\n";
    cout << "\t\t\t\tQuraan playlist manager menu\n";
    cout << "========================================================================================================================\n";
    cout << "\t\t|1. Add a new playlist                                     |\n";
    cout << "\t\t|2. Add Shurah to an existing playlist                     |\n";
    cout << "\t\t|3. Remove Shurah from an existing playlist                |\n";
    cout << "\t\t|4. Update the order of existing playlist                  |\n";
    cout << "\t\t|5. Display all current playlists                          |\n";
    cout << "\t\t|6. Display all playlists shurah                           |\n";
    cout << "\t\t|7. Display shurah in a specific playlist                  |\n";
    cout << "\t\t|8. Play shurah from specific playlist                     |\n";
    cout << "\t\t|   Use left arrow (<-) to play the previous shurah        |\n";
    cout << "\t\t|   Use right arrow (->) to play the next shurah           |\n";
    cout << "\t\t|   Use up arrow to pause the current shurah               |\n";
    cout << "\t\t|   Use down arrow to resume the current shurah            |\n";
    cout << "\t\t|   Press q to exit current playlist & return back to menu |\n";
    cout << "\t\t|9. Save an existing playlist to a file                    |\n";
    cout << "\t\t|10. Load an existing playlist from a file                 |\n";
    cout << "\t\t|11. Remove an existing playlist                           |\n";
    cout << "\t\t|12. Exit                                                  |\n";
    cout << "========================================================================================================================\n";
    Number = ReadNumberInRange(1, 12, "Your choice: ");
    cout << "========================================================================================================================\n\n";
}

int main()
{
    PlaylistManager Manager1;
    Playlist playlist1;
    Surah surah;
    surah.SetData("Al-Fatiha", "Makkah", "Al-Fatiha.wav");
    surah.PlaySurah();
    int Index;
    int Choice;
    do
    {
        PrintList(Choice);
        switch (Choice)
        {
        case 1: // Add new playlist
            playlist1.SetName(ReadString("Enter reader name: "));
            Manager1.InsertEnd(playlist1);
            system("cls");
            cout << "Playlist has been added.\n";
            break;
        case 2: // Add surah to playlist
            surah.SetData(ReadString("Enter surah name: "), ReadString("Enter surah type: "), ReadString("Enter surah path: "));
            Manager1.GetIndex(ReadNumberInRange(1, Manager1.GetNumOfLists(), "Enter playlist number: ")).InsertBegin(surah);
            system("cls");
            cout << "Shurah has been added.\n";
            break;
        case 3: // Remove surah from playlist
            Manager1.GetByName(ReadString("Enter playlist name: "));
            system("cls");
            cout << "Shurah has been removed.\n";
            break;
        case 4: // Update order of playlist

            break;
        case 5: // Display playlists
            system("cls");
            cout << "The current playlists are : \n";
            Manager1.Display();
            break;
        case 6: // Display Surahs
            system("cls");
            DisplayPlaylistsShurahs(Manager1);
            break;
        case 7: // Display surah in playlist
            system("cls");
            Manager1.GetByName(ReadString("Enter the playlist name: ")).Display();
            break;
        case 8: // Play surah in playlist
            Manager1.GetByName(ReadString("Enter the playlist name: ")).GetByName("Enter the shurah name: ").PlaySurah();
            break;
        case 9: // Save to file

            break;
        case 10: // Get from file

            break;
        case 11: // Remove a playlist
            Manager1.DeleteIndex(ReadNumberInRange(1, Manager1.GetNumOfLists(), "Enter playlist number: "));
            break;
        default:
            break;
        }
    } while (Choice != 12);

    return 0;
}