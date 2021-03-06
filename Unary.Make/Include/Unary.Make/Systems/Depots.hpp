/*
MIT License

Copyright (c) 2020 Unary Incorporated

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <cstdio>

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

#include <Unary.Make/Systems/System.hpp>
#include <Unary.Make/Structs/DepotManifest.hpp>

#include <Unary.Make/Systems/Arguments.hpp>
#include <Unary.Make/Units/Static.hpp>

namespace Unary::Make::Systems
{
    DeclareSystem(Depots)
    {
        private:

            std::unordered_map<std::string, Structs::DepotManifest> Depots;

        public:

            DeclareType(Unary::Make::Systems::Depots)

            bool ParseDepot(const std::string& Path);

            void Init()
            {
                std::vector<std::string>* Args = SysPtr->Get<Arguments>()->Get();

                for(size_t i = 2; i < Args->size(); ++i)
                {
                    for(const auto& Path : std::filesystem::directory_iterator((*Args)[i]))
                    {
                        if(Path.is_directory())
                        {
                            std::string DepotManifest = Path.path().string() + "/Depot.json";
                            if(std::filesystem::exists(DepotManifest))
                            {
                                ParseDepot(DepotManifest);
                            }
                        }
                    }
                }

                for (auto& Depot : Depots)
                {
                    std::cout << "Depot: " << Depot.first << std::endl;
                }
            }

            void Clear()
            {

            }
    };
}