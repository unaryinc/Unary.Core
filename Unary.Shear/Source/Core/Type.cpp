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

#include <Unary.Shear/Core/Type.hpp>

namespace Unary::Shear::Core
{
	Type::Type(const char* NewName, const Type* NewBaseType) :
	Name(NewName), BaseType(NewBaseType), Hash(Unary::Shear::Core::App::Get()->Hash(NewName, std::char_traits<char>::length(NewName)))
	{

	}

	Type::~Type() = default;

    bool Type::IsTypeOf(uint64_t Hash) const
    {
        const Type* Current = this;
        while (Current)
        {
            if (Current->GetHash() == Hash)
            {
                return true;
            }

            Current = Current->GetBaseType();
        }

        return false;
    }

    bool Type::IsTypeOf(const Type* NewType) const
    {
        if (NewType == nullptr)
        {
            return true;
        }

        const Type* Current = this;
        while (Current)
        {
            if (Current == NewType || Current->GetHash() == NewType->GetHash())
            {
                return true;
            }

            Current = Current->GetBaseType();
        }

        return false;
    }
}