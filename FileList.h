/*
 * FileList.h
 *
 *  Created on: 11/dic/2013
 *      Author: Stefano Ceccherini (stefano.ceccherini@gmail.com)
 */

#ifndef __FILELIST_H_
#define __FILELIST_H_

#include <StringList.h>

class BPath;
class FileList : private BStringList {
public:
	FileList(const bool ownsFiles);
	virtual ~FileList();

	void AddItem(const BString& fileName);
	BString ItemAt(int32 i) const;

	int32 CountItems() const;

	static FileList* CreateFileList(const BPath &path);

private:
	bool fOwnsFiles;
};


#endif /* __FILELIST_H_ */
