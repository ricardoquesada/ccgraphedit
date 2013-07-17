#ifndef FILEUTIL_H
#define FILEUTIL_H

#include "dirent.h"
#include "errno.h"
#include "string.h"
#include "stdio.h"

class FileUtil
{
public:

    template <class T>
    static bool EnumerateDirectoryT(const char* root, const char* path, T* target, void (T::*selector)(const char*, const char*, bool))
    {
        if (!path)
            path = root;

        char fullpath[2048];
        strncpy(fullpath, path, sizeof(fullpath));
        int len = strlen(path);

        DIR* directory = opendir(path);
        if (!directory)
            return false;

        seekdir(directory, 0);

        dirent* de;
        while ((de = readdir(directory)))
        {
            if (*de->d_name == '.')
            {
                if (de->d_namlen == 1)
                    continue;
                if (de->d_namlen == 2 && de->d_name[1] == '.')
                    continue;
            }

            sprintf(&fullpath[len], "/%s", de->d_name);

            DIR* d = opendir(fullpath);
            if (d)
                closedir(d);

            (target->*selector)(root, fullpath, d ? true : false);

            if (d)
            {
                if (!EnumerateDirectoryT(root, fullpath, target, selector))
                    return false;
            }
        }

        return true;
    }
};

#endif // FILEUTIL_H
