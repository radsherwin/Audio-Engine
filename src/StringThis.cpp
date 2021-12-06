//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "StringThis.h"


StringThis::StringThis(SndId status)
{
	switch (status)
	{
	case SndId::BASSOON_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::BASSOON_ID));
		break;
	case SndId::BASSOON2_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::BASSOON2_ID));
		break;
	case SndId::BASSOON3_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::BASSOON3_ID));
		break;
	case SndId::BASSOON4_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::BASSOON4_ID));
		break;
	case SndId::BASSOON5_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::BASSOON5_ID));
		break;

	case SndId::STRINGS_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::STRINGS_ID));
		break;

	case SndId::FIDDLE_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::FIDDLE_ID));
		break;

	case SndId::SONGA_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::SONGA_ID));
		break;

	case SndId::SONGB_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::SONGB_ID));
		break;

	case SndId::OBOE2_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::OBOE2_ID));
		break;

	case SndId::A_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::A_ID));
		break;

	case SndId::ATOB_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::ATOB_ID));
		break;

	case SndId::B_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::B_ID));
		break;

	case SndId::BTOC_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::BTOC_ID));
		break;

	case SndId::C_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::C_ID));
		break;

	case SndId::CTOA_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::CTOA_ID));
		break;

	case SndId::END_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::END_ID));
		break;

	case SndId::INTRO_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::INTRO_ID));
		break;

	case SndId::ELECTRO_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::ELECTRO_ID));
		break;

	case SndId::ALARM_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::ALARM_ID));
		break;

	case SndId::BEETHOVEN_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::BEETHOVEN_ID));
		break;

	case SndId::DIAL_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::DIAL_ID));
		break;

	case SndId::MOON_PATROL_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::MOON_PATROL_ID));
		break;

	case SndId::SEQUENCE_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::SEQUENCE_ID));
		break;

	case SndId::DONKEY_ID:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::DONKEY_ID));
		break;

	case SndId::SND_A:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::SND_A));
		break;

	case SndId::SND_B:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::SND_B));
		break;

	case SndId::SND_C:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::SND_C));
		break;

	case SndId::SND_D:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::SND_D));
		break;

	case SndId::SND_E:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::SND_E));
		break;

	case SndId::SND_F:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::SND_F));
		break;

	case SndId::SND_G:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::SND_G));
		break;

	case SndId::SND_HH:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::SND_HH));
		break;

	case SndId::SND_I:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::SND_I));
		break;

	case SndId::SND_J:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::SND_J));
		break;

	case SndId::SND_K:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::SND_K));
		break;

	case SndId::Uninitialized:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::Uninitialized));
		break;

	case SndId::EMPTY:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(SndId::EMPTY));
		break;

	default:
		assert(false);
	}
}

StringThis::StringThis(Handle::Status status)
{
	switch (status)
	{
	case Handle::Status::SUCCESS:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Handle::SUCCESS));
		break;

	case Handle::Status::INSUFFIENT_SPACE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Handle::INSUFFIENT_SPACE));
		break;

	case Handle::Status::INVALID_HANDLE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Handle::INVALID_HANDLE));
		break;

	case Handle::Status::VALID_HANDLE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Handle::VALID_HANDLE));
		break;

	case Handle::Status::HANDLE_ERROR:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Handle::HANDLE_ERROR));
		break;

	default:
		assert(false);
	}
}

StringThis::StringThis(Wave::ID status)
{
	switch (status)
	{
	case Wave::ID::Bassoon:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Bassoon));
		break;

	case Wave::ID::Calliope:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Calliope));
		break;

	case Wave::ID::Fiddle:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Fiddle));
		break;

	case Wave::ID::Oboe:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Oboe));
		break;

	case Wave::ID::SongA:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::SongA));
		break;

	case Wave::ID::SongB:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::SongB));
		break;

	case Wave::ID::Strings:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Strings));
		break;

	case Wave::ID::A:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::A));
		break;

	case Wave::ID::AtoB:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::AtoB));
		break;

	case Wave::ID::B:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::B));
		break;

	case Wave::ID::BtoC:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::BtoC));
		break;

	case Wave::ID::C:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::C));
		break;

	case Wave::ID::CtoA:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::CtoA));
		break;

	case Wave::ID::End:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::End));
		break;

	case Wave::ID::Intro:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Intro));
		break;

	case Wave::ID::Electro:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Electro));
		break;

	case Wave::ID::Alarm:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Alarm));
		break;

	case Wave::ID::Beethoven:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Beethoven));
		break;

	case Wave::ID::Coma:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Coma));
		break;

	case Wave::ID::Dial:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Dial));
		break;

	case Wave::ID::MoonPatrol:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::MoonPatrol));
		break;

	case Wave::ID::Sequence:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Sequence));
		break;

	case Wave::ID::Donkey:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Donkey));
		break;

	case Wave::ID::Uninitialized:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Uninitialized));
		break;

	case Wave::ID::Empty:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Empty));
		break;

	default:
		assert(false);
	}

}

StringThis::StringThis(WaveTable::Status status)
{
	switch (status)
	{
	case WaveTable::Status::EMPTY:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(WaveTable::EMPTY));
		break;

	case WaveTable::Status::PENDING:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(WaveTable::PENDING));
		break;

	case WaveTable::Status::READY:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(WaveTable::READY));
		break;

	default:
		assert(false);
	}
}

StringThis::operator char* ()
{
	return this->buffer;
}

// --- End of File ---