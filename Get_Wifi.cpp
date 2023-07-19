#include <Windows.h>
#include <Lmcons.h> 
#include <Wlanapi.h>
#include <string>

int main() 
{
    // Get a handle to the Windows interface
    HW_PROFILE_INFO hwProfileInfo;
    DWORD dwSize = sizeof(hwProfileInfo);
    DWORD dwResult = WlanGetProfileList(NULL, &dwSize, &hwProfileInfo);

    // Loop through all profiles
    for (int i = 0; i < hwProfileInfo.dwNumberOfItems; i++) 
    {
        // Get the profile name
        WCHAR strProfileName[256];
        DWORD dwResult = WlanGetProfileName(hwProfileInfo.hwProfileInfo[i].dwIndex, 
            NULL, &dwSize, strProfileName);

        // Get the profile information
        WLAN_PROFILE_INFO profileInfo;
        DWORD dwSize = sizeof(profileInfo);
        WlanGetProfile(NULL, hwProfileInfo.hwProfileInfo[i].dwIndex, &profileInfo, &dwSize);

        // Check if it is a WiFi profile
        if (profileInfo.wlanProfile.fProfile.dwFlags & WLAN_PROFILE_FLAG_ON_DEMAND) 
        {
            // Get the password
            std::wstring password = std::wstring(profileInfo.wlanProfile.pswProfile.strPassword);

            // Print the password
            std::wcout << L"Password for " << strProfileName << L": " << password << std::endl;
        }
    }
}
