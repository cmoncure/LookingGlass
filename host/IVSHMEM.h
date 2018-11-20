/*
Looking Glass - KVM FrameRelay (KVMFR) Client
Copyright (C) 2017 Geoffrey McRae <geoff@hostfission.com>
https://looking-glass.hostfission.com

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA
*/

#pragma once

#define W32_LEAN_AND_MEAN
#include <windows.h>
#include <stdbool.h>
#include <vector>


class IVSHMEM
{
public:
  static IVSHMEM * Get(uint8_t device)
  {
    if (!m_instance)
      m_instance = new IVSHMEM(device);
    return m_instance;
  }
  static void Enumerate();

  bool Initialize();
  void DeInitialize();
  bool IsInitialized();

  UINT64 GetSize();
  UINT16 GetPeerID();
  UINT16 GetVectors();
  void * GetMemory();
  HANDLE CreateVectorEvent(UINT16 vector);
  bool   RingDoorbell(UINT16 peerID, UINT16 door);

protected:


private:
  static std::vector<IVSHMEM *> m_shms;
  static IVSHMEM * m_instance;

  IVSHMEM(uint8_t device);
  ~IVSHMEM();

  bool   m_initialized;
  HANDLE m_handle;

  UINT8  m_enumeration;
  UINT64 m_size   ; bool m_gotSize  ;
  UINT16 m_peerID ; bool m_gotPeerID;
  void * m_memory ; bool m_gotMemory;
  UINT16 m_vectors; bool m_gotVectors;
};
