
#ifndef _CHUNK_SERVER_TRANSFER_APP_HPP
#define _CHUNK_SERVER_TRANSFER_APP_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <Ice/Application.h>
#include "TransferImpl.hpp"
#include "ChunkManager.hpp"


using namespace std;
namespace tfs
{

	class TransferApp : virtual public Ice::Application 
	{
	public:
		TransferApp(ChunkManager * chunk_mgr){
			m_chunk_mgr = chunk_mgr;
		}

		int run(int argc,char ** argv) 
		{
			// configuration file
			//assert(argc == 2);
			ChunkServerConf * pConf = ChunkServerConf::getInstance(); 

			stringstream ss;
			ss << "tcp -p " << pConf->DATA_SOCKET_PORT;

			m_adapter = communicator()->createObjectAdapterWithEndpoints("chunkserver", ss.str());

			slice::TransferPtr pTransfer= new TransferImpl(m_chunk_mgr);

			m_adapter->add(pTransfer, communicator()->stringToIdentity("Transfer"));            
			m_adapter->activate();

			communicator()->waitForShutdown();

			if (interrupted()) {
				LOG_INFO("TransferApp() Received signal, shutting down");
			}

			m_adapter = 0;
			log4cplus::getNDC().pop();
			return 0;
		}
	private:
		Ice::ObjectAdapterPtr m_adapter;
		ChunkManager * m_chunk_mgr;
	};
}

#endif
