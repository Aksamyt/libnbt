// libnbt++ --- A C++ library for parsing, generating and manipulating NBT
// Copyright (C) 2018 Alexandre Szymocha <alexandre@szymocha.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#define NBT_UNIT_TEST_
#include "nbt.hpp"

#include "catch.hpp"

#include <algorithm>
#include <sstream>

using namespace nbt::unqualified;

auto
make_stream(char const *s, std::size_t const len)
{
	return std::istringstream(std::string(s, len));
}

TEST_CASE( "Sample nbt files" )
{
	SECTION( "Notch's test.nbt" )
	{
		char const bytes[] = "\x0A\x00\x0B\x68\x65\x6C\x6C\x6F\x20\x77\x6F\x72\x6C\x64\x08\x00\x04\x6E\x61\x6D\x65\x00\x09\x42\x61\x6E\x61\x6E\x72\x61\x6D\x61\x00";
		auto iss = make_stream(bytes, sizeof(bytes) - 1);
		auto res = nbt::parse(iss);
		CHECK( res->index() == compound );
		CHECK( compound(res).begin()->first == "hello world" );
		CHECK
		(	compound(res)["hello world"]->index()
			== compound
		);
		CHECK
		(	compound(compound(res)["hello world"])
				.begin()->first
			== "name"
		);
		CHECK
		(	compound(compound(res)["hello world"])
				["name"]->index()
			== string
		);
		CHECK
		(	string
			(	compound(compound(res)["hello world"])
					["name"]
			) == "Bananrama"
		);
	}

	SECTION( "Notch's bigtest.nbt (uncompressed)" )
	{
		char const bytes[] = "\x0A\x00\x05\x4C\x65\x76\x65\x6C\x04\x00\x08\x6C\x6F\x6E\x67\x54\x65\x73\x74\x7F\xFF\xFF\xFF\xFF\xFF\xFF\xFF\x02\x00\x09\x73\x68\x6F\x72\x74\x54\x65\x73\x74\x7F\xFF\x08\x00\x0A\x73\x74\x72\x69\x6E\x67\x54\x65\x73\x74\x00\x29\x48\x45\x4C\x4C\x4F\x20\x57\x4F\x52\x4C\x44\x20\x54\x48\x49\x53\x20\x49\x53\x20\x41\x20\x54\x45\x53\x54\x20\x53\x54\x52\x49\x4E\x47\x20\xC3\x85\xC3\x84\xC3\x96\x21\x05\x00\x09\x66\x6C\x6F\x61\x74\x54\x65\x73\x74\x3E\xFF\x18\x32\x03\x00\x07\x69\x6E\x74\x54\x65\x73\x74\x7F\xFF\xFF\xFF\x0A\x00\x14\x6E\x65\x73\x74\x65\x64\x20\x63\x6F\x6D\x70\x6F\x75\x6E\x64\x20\x74\x65\x73\x74\x0A\x00\x03\x68\x61\x6D\x08\x00\x04\x6E\x61\x6D\x65\x00\x06\x48\x61\x6D\x70\x75\x73\x05\x00\x05\x76\x61\x6C\x75\x65\x3F\x40\x00\x00\x00\x0A\x00\x03\x65\x67\x67\x08\x00\x04\x6E\x61\x6D\x65\x00\x07\x45\x67\x67\x62\x65\x72\x74\x05\x00\x05\x76\x61\x6C\x75\x65\x3F\x00\x00\x00\x00\x00\x09\x00\x0F\x6C\x69\x73\x74\x54\x65\x73\x74\x20\x28\x6C\x6F\x6E\x67\x29\x04\x00\x00\x00\x05\x00\x00\x00\x00\x00\x00\x00\x0B\x00\x00\x00\x00\x00\x00\x00\x0C\x00\x00\x00\x00\x00\x00\x00\x0D\x00\x00\x00\x00\x00\x00\x00\x0E\x00\x00\x00\x00\x00\x00\x00\x0F\x09\x00\x13\x6C\x69\x73\x74\x54\x65\x73\x74\x20\x28\x63\x6F\x6D\x70\x6F\x75\x6E\x64\x29\x0A\x00\x00\x00\x02\x08\x00\x04\x6E\x61\x6D\x65\x00\x0F\x43\x6F\x6D\x70\x6F\x75\x6E\x64\x20\x74\x61\x67\x20\x23\x30\x04\x00\x0A\x63\x72\x65\x61\x74\x65\x64\x2D\x6F\x6E\x00\x00\x01\x26\x52\x37\xD5\x8D\x00\x08\x00\x04\x6E\x61\x6D\x65\x00\x0F\x43\x6F\x6D\x70\x6F\x75\x6E\x64\x20\x74\x61\x67\x20\x23\x31\x04\x00\x0A\x63\x72\x65\x61\x74\x65\x64\x2D\x6F\x6E\x00\x00\x01\x26\x52\x37\xD5\x8D\x00\x01\x00\x08\x62\x79\x74\x65\x54\x65\x73\x74\x7F\x07\x00\x65\x62\x79\x74\x65\x41\x72\x72\x61\x79\x54\x65\x73\x74\x20\x28\x74\x68\x65\x20\x66\x69\x72\x73\x74\x20\x31\x30\x30\x30\x20\x76\x61\x6C\x75\x65\x73\x20\x6F\x66\x20\x28\x6E\x2A\x6E\x2A\x32\x35\x35\x2B\x6E\x2A\x37\x29\x25\x31\x30\x30\x2C\x20\x73\x74\x61\x72\x74\x69\x6E\x67\x20\x77\x69\x74\x68\x20\x6E\x3D\x30\x20\x28\x30\x2C\x20\x36\x32\x2C\x20\x33\x34\x2C\x20\x31\x36\x2C\x20\x38\x2C\x20\x2E\x2E\x2E\x29\x29\x00\x00\x03\xE8\x00\x3E\x22\x10\x08\x0A\x16\x2C\x4C\x12\x46\x20\x04\x56\x4E\x50\x5C\x0E\x2E\x58\x28\x02\x4A\x38\x30\x32\x3E\x54\x10\x3A\x0A\x48\x2C\x1A\x12\x14\x20\x36\x56\x1C\x50\x2A\x0E\x60\x58\x5A\x02\x18\x38\x62\x32\x0C\x54\x42\x3A\x3C\x48\x5E\x1A\x44\x14\x52\x36\x24\x1C\x1E\x2A\x40\x60\x26\x5A\x34\x18\x06\x62\x00\x0C\x22\x42\x08\x3C\x16\x5E\x4C\x44\x46\x52\x04\x24\x4E\x1E\x5C\x40\x2E\x26\x28\x34\x4A\x06\x30\x00\x3E\x22\x10\x08\x0A\x16\x2C\x4C\x12\x46\x20\x04\x56\x4E\x50\x5C\x0E\x2E\x58\x28\x02\x4A\x38\x30\x32\x3E\x54\x10\x3A\x0A\x48\x2C\x1A\x12\x14\x20\x36\x56\x1C\x50\x2A\x0E\x60\x58\x5A\x02\x18\x38\x62\x32\x0C\x54\x42\x3A\x3C\x48\x5E\x1A\x44\x14\x52\x36\x24\x1C\x1E\x2A\x40\x60\x26\x5A\x34\x18\x06\x62\x00\x0C\x22\x42\x08\x3C\x16\x5E\x4C\x44\x46\x52\x04\x24\x4E\x1E\x5C\x40\x2E\x26\x28\x34\x4A\x06\x30\x00\x3E\x22\x10\x08\x0A\x16\x2C\x4C\x12\x46\x20\x04\x56\x4E\x50\x5C\x0E\x2E\x58\x28\x02\x4A\x38\x30\x32\x3E\x54\x10\x3A\x0A\x48\x2C\x1A\x12\x14\x20\x36\x56\x1C\x50\x2A\x0E\x60\x58\x5A\x02\x18\x38\x62\x32\x0C\x54\x42\x3A\x3C\x48\x5E\x1A\x44\x14\x52\x36\x24\x1C\x1E\x2A\x40\x60\x26\x5A\x34\x18\x06\x62\x00\x0C\x22\x42\x08\x3C\x16\x5E\x4C\x44\x46\x52\x04\x24\x4E\x1E\x5C\x40\x2E\x26\x28\x34\x4A\x06\x30\x00\x3E\x22\x10\x08\x0A\x16\x2C\x4C\x12\x46\x20\x04\x56\x4E\x50\x5C\x0E\x2E\x58\x28\x02\x4A\x38\x30\x32\x3E\x54\x10\x3A\x0A\x48\x2C\x1A\x12\x14\x20\x36\x56\x1C\x50\x2A\x0E\x60\x58\x5A\x02\x18\x38\x62\x32\x0C\x54\x42\x3A\x3C\x48\x5E\x1A\x44\x14\x52\x36\x24\x1C\x1E\x2A\x40\x60\x26\x5A\x34\x18\x06\x62\x00\x0C\x22\x42\x08\x3C\x16\x5E\x4C\x44\x46\x52\x04\x24\x4E\x1E\x5C\x40\x2E\x26\x28\x34\x4A\x06\x30\x00\x3E\x22\x10\x08\x0A\x16\x2C\x4C\x12\x46\x20\x04\x56\x4E\x50\x5C\x0E\x2E\x58\x28\x02\x4A\x38\x30\x32\x3E\x54\x10\x3A\x0A\x48\x2C\x1A\x12\x14\x20\x36\x56\x1C\x50\x2A\x0E\x60\x58\x5A\x02\x18\x38\x62\x32\x0C\x54\x42\x3A\x3C\x48\x5E\x1A\x44\x14\x52\x36\x24\x1C\x1E\x2A\x40\x60\x26\x5A\x34\x18\x06\x62\x00\x0C\x22\x42\x08\x3C\x16\x5E\x4C\x44\x46\x52\x04\x24\x4E\x1E\x5C\x40\x2E\x26\x28\x34\x4A\x06\x30\x00\x3E\x22\x10\x08\x0A\x16\x2C\x4C\x12\x46\x20\x04\x56\x4E\x50\x5C\x0E\x2E\x58\x28\x02\x4A\x38\x30\x32\x3E\x54\x10\x3A\x0A\x48\x2C\x1A\x12\x14\x20\x36\x56\x1C\x50\x2A\x0E\x60\x58\x5A\x02\x18\x38\x62\x32\x0C\x54\x42\x3A\x3C\x48\x5E\x1A\x44\x14\x52\x36\x24\x1C\x1E\x2A\x40\x60\x26\x5A\x34\x18\x06\x62\x00\x0C\x22\x42\x08\x3C\x16\x5E\x4C\x44\x46\x52\x04\x24\x4E\x1E\x5C\x40\x2E\x26\x28\x34\x4A\x06\x30\x00\x3E\x22\x10\x08\x0A\x16\x2C\x4C\x12\x46\x20\x04\x56\x4E\x50\x5C\x0E\x2E\x58\x28\x02\x4A\x38\x30\x32\x3E\x54\x10\x3A\x0A\x48\x2C\x1A\x12\x14\x20\x36\x56\x1C\x50\x2A\x0E\x60\x58\x5A\x02\x18\x38\x62\x32\x0C\x54\x42\x3A\x3C\x48\x5E\x1A\x44\x14\x52\x36\x24\x1C\x1E\x2A\x40\x60\x26\x5A\x34\x18\x06\x62\x00\x0C\x22\x42\x08\x3C\x16\x5E\x4C\x44\x46\x52\x04\x24\x4E\x1E\x5C\x40\x2E\x26\x28\x34\x4A\x06\x30\x00\x3E\x22\x10\x08\x0A\x16\x2C\x4C\x12\x46\x20\x04\x56\x4E\x50\x5C\x0E\x2E\x58\x28\x02\x4A\x38\x30\x32\x3E\x54\x10\x3A\x0A\x48\x2C\x1A\x12\x14\x20\x36\x56\x1C\x50\x2A\x0E\x60\x58\x5A\x02\x18\x38\x62\x32\x0C\x54\x42\x3A\x3C\x48\x5E\x1A\x44\x14\x52\x36\x24\x1C\x1E\x2A\x40\x60\x26\x5A\x34\x18\x06\x62\x00\x0C\x22\x42\x08\x3C\x16\x5E\x4C\x44\x46\x52\x04\x24\x4E\x1E\x5C\x40\x2E\x26\x28\x34\x4A\x06\x30\x00\x3E\x22\x10\x08\x0A\x16\x2C\x4C\x12\x46\x20\x04\x56\x4E\x50\x5C\x0E\x2E\x58\x28\x02\x4A\x38\x30\x32\x3E\x54\x10\x3A\x0A\x48\x2C\x1A\x12\x14\x20\x36\x56\x1C\x50\x2A\x0E\x60\x58\x5A\x02\x18\x38\x62\x32\x0C\x54\x42\x3A\x3C\x48\x5E\x1A\x44\x14\x52\x36\x24\x1C\x1E\x2A\x40\x60\x26\x5A\x34\x18\x06\x62\x00\x0C\x22\x42\x08\x3C\x16\x5E\x4C\x44\x46\x52\x04\x24\x4E\x1E\x5C\x40\x2E\x26\x28\x34\x4A\x06\x30\x00\x3E\x22\x10\x08\x0A\x16\x2C\x4C\x12\x46\x20\x04\x56\x4E\x50\x5C\x0E\x2E\x58\x28\x02\x4A\x38\x30\x32\x3E\x54\x10\x3A\x0A\x48\x2C\x1A\x12\x14\x20\x36\x56\x1C\x50\x2A\x0E\x60\x58\x5A\x02\x18\x38\x62\x32\x0C\x54\x42\x3A\x3C\x48\x5E\x1A\x44\x14\x52\x36\x24\x1C\x1E\x2A\x40\x60\x26\x5A\x34\x18\x06\x62\x00\x0C\x22\x42\x08\x3C\x16\x5E\x4C\x44\x46\x52\x04\x24\x4E\x1E\x5C\x40\x2E\x26\x28\x34\x4A\x06\x30\x06\x00\x0A\x64\x6F\x75\x62\x6C\x65\x54\x65\x73\x74\x3F\xDF\x8F\x6B\xBB\xFF\x6A\x5E\x00";
		auto iss = make_stream(bytes, sizeof(bytes) - 1);
		auto res = nbt::parse(iss);
		CHECK( res->index() == compound );
		CHECK( compound(res).begin()->first == "Level" );
		CHECK( compound(res)["Level"]->index() == compound );
		CHECK
		(	compound(compound(res)["Level"]).size()
			== 11
		);
		CHECK
		(	compound(compound(res)["Level"])
				["nested compound test"]->index()
			== compound
		);
		// assume .index() is correct
		CHECK
		(	string
			(
				compound
				(	compound
					(	compound
						(	compound(res)
							["Level"]
						)["nested compound test"]
					)["egg"]
				)["name"]
			) == "Eggbert"
		);
		CHECK
		(	float_
			(
				compound
				(	compound
					(	compound
						(	compound(res)
							["Level"]
						)["nested compound test"]
					)["egg"]
				)["value"]
			) == 0.5
		);
		CHECK
		(	string
			(
				compound
				(	compound
					(	compound
						(	compound(res)
							["Level"]
						)["nested compound test"]
					)["ham"]
				)["name"]
			) == "Hampus"
		);
		CHECK
		(	float_
			(
				compound
				(	compound
					(	compound
						(	compound(res)
							["Level"]
						)["nested compound test"]
					)["ham"]
				)["value"]
			) == 0.75
		);
		// intTest
		CHECK
		(	compound(compound(res)["Level"])
				["intTest"]->index()
			== int_
		);
		CHECK
		(	int_
			(	compound(compound(res)["Level"])
					["intTest"]
			) == 2147483647
		);
		// byteTest
		CHECK
		(	compound(compound(res)["Level"])
				["byteTest"]->index()
			== byte
		);
		CHECK
		(	byte
			(	compound(compound(res)["Level"])
					["byteTest"]
			) == 127
		);
		// stringTest
		CHECK
		(	compound(compound(res)["Level"])
				["stringTest"]->index()
			== string
		);
		CHECK
		(	string
			(	compound(compound(res)["Level"])
					["stringTest"]
			) == "HELLO WORLD THIS IS A TEST STRING \xc3\x85\xc3\x84\xc3\x96!"
		);
		// listTest (long)
		CHECK
		(	compound(compound(res)["Level"])
				["listTest (long)"]->index()
			== list
		);
		CHECK
		(	list
			(	compound(compound(res)["Level"])
					["listTest (long)"]
			).front().index() == long_
		);
		CHECK
		(	list.as<long_>
			(	compound(compound(res)["Level"])
					["listTest (long)"]
			) == std::vector{11L, 12L, 13L, 14L, 15L}
		);
		// doubleTest
		CHECK
		(	compound(compound(res)["Level"])
				["doubleTest"]->index()
			== double_
		);
		CHECK
		(	double_
			(	compound(compound(res)["Level"])
					["doubleTest"]
			) == 0.49312871321823148
		);
		// floatTest
		CHECK
		(	compound(compound(res)["Level"])
				["floatTest"]->index()
			== float_
		);
		CHECK
		(	float_
			(	compound(compound(res)["Level"])
					["floatTest"]
			) == 0.49823147058486938f
		);
		// longTest
		CHECK
		(	compound(compound(res)["Level"])
				["longTest"]->index()
			== long_
		);
		CHECK
		(	long_
			(	compound(compound(res)["Level"])
					["longTest"]
			) == 9223372036854775807L
		);
		// listTest (compound) (assume .index() is correct)
		CHECK
		(	compound(compound(res)["Level"])
				["listTest (compound)"]->index()
			== list
		);
		CHECK
		(	list
			(	compound(compound(res)["Level"])
					["listTest (compound)"]
			).front().index() == compound
		);
		CHECK
		(	long_
			(	list.as<compound>
				(	compound
					(	compound(res)
						["Level"]
					)["listTest (compound)"]
				)[0]["created-on"]
			) == 1264099775885L
		);
		CHECK
		(	string
			(	list.as<compound>
				(	compound
					(	compound(res)
						["Level"]
					)["listTest (compound)"]
				)[0]["name"]
			) == "Compound tag #0"
		);
		CHECK
		(	long_
			(	list.as<compound>
				(	compound
					(	compound(res)
						["Level"]
					)["listTest (compound)"]
				)[1]["created-on"]
			) == 1264099775885L
		);
		CHECK
		(	string
			(	list.as<compound>
				(	compound
					(	compound(res)
						["Level"]
					)["listTest (compound)"]
				)[1]["name"]
			) == "Compound tag #1"
		);
		// byteArrayTest (the first 1000 values of (n*n*255+n*7)%100, starting with n=0 (0, 62, 34, 16, 8, ...))
		CHECK
		(	compound(compound(res)["Level"])
				["byteArrayTest (the first 1000 values of (n*n*255+n*7)%100, starting with n=0 (0, 62, 34, 16, 8, ...))"]->index()
			== byte_array
		);
		CHECK
		(	byte_array
			(	compound(compound(res)["Level"])
					["byteArrayTest (the first 1000 values of (n*n*255+n*7)%100, starting with n=0 (0, 62, 34, 16, 8, ...))"]
			).size() == 1000
		);
		std::vector<int8_t> byteArrayTest(1000U);
		std::generate
		(	byteArrayTest.begin(), byteArrayTest.end()
		,	[n = -1] (void) mutable -> std::int8_t {
				return ++n, (n * n * 255 + n * 7) % 100;
			}
		);
		CHECK
		(	byte_array
			(	compound(compound(res)["Level"])
					["byteArrayTest (the first 1000 values of (n*n*255+n*7)%100, starting with n=0 (0, 62, 34, 16, 8, ...))"]
			) == byteArrayTest
		);
		// shortTest
		CHECK
		(	compound(compound(res)["Level"])
				["shortTest"]->index()
			== short_
		);
		CHECK
		(	short_
			(	compound(compound(res)["Level"])
					["shortTest"]
			) == 32767
		);
	}
}
