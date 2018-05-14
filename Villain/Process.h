#pragma once

#define PatchCode_Success					0
#define PatchCode_Header_Not_Found			1
#define PatchCode_Could_Not_Open_Process	2

class Process
{
	private:
		char* _directory;

	public:
		char* GetDirectory()
		{
			return _directory;
		}

		void Initialize();

		int PatchCode();
		virtual void OnPatchCode(HANDLE process) = 0;
		bool InstallDetours();
		virtual void OnInstallDetours() = 0;

		bool GetSectionHeaderInfo(char* sectionName, PIMAGE_SECTION_HEADER& dest);

		void ResumeAllThreads();
};