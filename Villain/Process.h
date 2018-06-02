#pragma once

#define PatchCode_Success					0
#define PatchCode_Header_Not_Found			1
#define PatchCode_Could_Not_Open_Process	2

[event_source(native)]
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
		__event void OnPatchCode(HANDLE process);
		/*
		virtual void OnPatchCode(HANDLE process)
		{

		}
		*/

		bool InstallDetours();
		__event void OnInstallDetours();
		/*
		virtual void OnInstallDetours()
		{

		}
		*/

		bool GetSectionHeaderInfo(char* sectionName, PIMAGE_SECTION_HEADER& dest);

		void ResumeAllThreads();
};