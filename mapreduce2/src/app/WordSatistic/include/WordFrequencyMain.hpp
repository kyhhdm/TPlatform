/**
 * @file WordFrequencyMain.hpp
 *
 * @author PengBo
 * @date 2007-12-18
 * */
#ifndef WORDFREQUENCYMAIN_HPP
#define WORDFREQUENCYMAIN_HPP

#include "IMapper.hpp"
#include "IFeeder.hpp"
#include "IReducer.hpp"
#include "IKeyHasher.hpp"
#include "IKeyComparison.hpp"
#include "KeyValue.hpp"
#include "Buffer.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <classloader/ClassLoader.h>
#include <classloader/IClassFactory.h>

namespace mapreduce{

    class WordFrequencyMain {
        public:
            WordFrequencyMain(string basename);
            ~WordFrequencyMain();

            void run(std::string& inFilePath);

        private:
            IFeeder* m_feeder;
            IMapper* m_mapper;
            IReducer* m_reducer;
            IKeyHasher* m_hasher;
            IKeyComparison* m_comparison;
            classloader::ClassLoader* m_loader;
            classloader::IClassFactory* m_factory;
    };
}
#endif

