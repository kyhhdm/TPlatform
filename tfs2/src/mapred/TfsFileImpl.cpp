/**
 * @file TfsFileImpl.cpp
 * .
 * 
 * @author Zhifeng YANG
 * @date 2007-11-29
 */

#include "TfsFileImpl.hpp"
#include "common/Exception.hpp"
#include <sstream>
using namespace tfs;
using namespace std;

TfsFileImpl::TfsFileImpl(const string& masterHost, int32_t port)
{
    m_address.name = "mapreduce_master";
    m_address.port = getpid();

    try {
        stringstream ss;
        ss << "ClientService:tcp -h " << masterHost << " -p " << port;
        // Initialize ice.
        Ice::CommunicatorPtr ic = Ice::initialize();
        Ice::ObjectPrx base = ic->stringToProxy(ss.str());
        m_service = tfs::slice::ClientServicePrx::checkedCast(base);
    } catch (Ice::Exception &ex) {
        cerr << "ERROR TfsFileImpl:: " << ex << endl;
    }
}

tfs::mapred::LocatedChunks TfsFileImpl::getChunksInfo(const std::string& filename)
{
    tfs::mapred::LocatedChunks lchks;
    
    try{
        LocatedChunks locatedChunks = m_service->getChunksInfo(m_address, filename);
        for (int i = 0; i < locatedChunks.size(); i++){
            tfs::mapred::LocatedChunk lchk;
            lchk.chkId = locatedChunks[i].chk.id;
            lchk.chkSize = locatedChunks[i].chk.size;
            for (int j = 0; j < locatedChunks[i].locations.size(); j++){
                tfs::mapred::Address address;
                address.name = locatedChunks[i].locations[j].name;
                address.port = locatedChunks[i].locations[j].port;
                lchk.locations.push_back(address);
            }
            lchks.push_back(lchk);
        }
        
    } catch (NoSuchFileOrDir &ex) {
        cerr << "WARN TfsFileImpl:: " << ex << endl;
    } catch (Ice::Exception &ex) {
        cerr << "WARN TfsFileImpl:: " << ex << endl;
    }
    return lchks;
}

bool TfsFileImpl::concatFiles(const std::vector<std::string> &srcFiles, const std::string& dst)
{
    try{
        m_service->concatFiles(srcFiles, dst);
        return true;
    }
    catch (NoSuchFileOrDir &ex) {
        cerr << "WARN TfsFileImpl:: " << ex << endl;
    }
    catch (FileOrDirAlreadyExists &ex) {
        cerr << "WARN TfsFileImpl:: " << ex << endl;
    } 
    catch (InvalidFileOrDirName &ex) {
        cerr << "WARN TfsFileImpl:: " << ex << endl;
    }
    catch (Ice::Exception &ex) {
        cerr << "WARN TfsFileImpl:: " << ex << endl;
    }
    return false;
}

