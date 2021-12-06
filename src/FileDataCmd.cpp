#include "FileDataCmd.h"
#include "QueueManager.h"
#include "StringThis.h"

using namespace ThreadFramework;

FileDataCmd::FileDataCmd(const char* const _pWaveName, Wave* _pWave)
	: Command(),
	poWfx(nullptr),
	poRawBuff(nullptr),
	rawBuffSize(0),
	pWave(_pWave),
	pWaveName(_pWaveName)
{
	assert(_pWaveName);
	this->LoadBuffer(_pWaveName);
}
void FileDataCmd::Execute()
{
	Debug::out("\n\n\t\t\t\t%s ---> Loaded\n\n", StringMe(pWave->id));
	assert(this->pWave);
	this->pWave->Register(poWfx, poRawBuff, rawBuffSize);
	delete this;
}

void FileDataCmd::LoadBuffer(const char* const _pWaveName)
{
	assert(_pWaveName);

	Debug::out("FileDataCmd::LoadBuffer(%s) start\n", _pWaveName);

	//--------------------------------------------------------
	// zero out wfx and the buffer
	//--------------------------------------------------------

	this->poWfx = new WAVEFORMATEXTENSIBLE();
	assert(this->poWfx);

	*this->poWfx = { 0 };    // zeros out the complete structure

	// -------------------------------------------------------
	// Open File
	// -------------------------------------------------------

	FileSlow::Handle FileHandle;
	FileSlow::Error ferror;

	// Open file
	ferror = FileSlow::Open(FileHandle, _pWaveName, FileSlow::Mode::READ);
	assert(ferror == FileSlow::Error::SUCCESS);

	// Set file to beginning
	ferror = FileSlow::Seek(FileHandle, FileSlow::Location::BEGIN, 0);
	assert(ferror == FileSlow::Error::SUCCESS);

	// -------------------------------------------------------
	// Find and load specific Chunks
	// -------------------------------------------------------

	DWORD dwChunkPosition;
	DWORD filetype;
	ChunkError cerror;

	// Scan to the RIFF and load file type
	cerror = FindChunk(FileHandle, fourccRIFF, this->rawBuffSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);
	cerror = ReadChunkData(FileHandle, &filetype, sizeof(DWORD), dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);

	// Make sure its not in the compressed format, WAVE format is uncompressed
	if (filetype != fourccWAVE)
	{
		assert(false);
	}

	// Read the FMT: format
	cerror = FindChunk(FileHandle, fourccFMT, this->rawBuffSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);
	cerror = ReadChunkData(FileHandle, this->poWfx, this->rawBuffSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);

	// Scan to the DATA chunk, read the size, allocate buffer of that size
	cerror = FindChunk(FileHandle, fourccDATA, this->rawBuffSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);

	//ThreadFramework::Debug::out("----CREATING NEW PDATABUFFER IN WAVE.CPP\n");
	this->poRawBuff = new unsigned char[this->rawBuffSize];
	assert(this->poRawBuff);

	// Fill the data...
	cerror = ReadChunkData(FileHandle, this->poRawBuff, this->rawBuffSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);

	ferror = FileSlow::Close(FileHandle);
	assert(ferror == FileSlow::Error::SUCCESS);

	Debug::out("FileDataCmd::LoadBuffer(%s) end\n", _pWaveName);
}