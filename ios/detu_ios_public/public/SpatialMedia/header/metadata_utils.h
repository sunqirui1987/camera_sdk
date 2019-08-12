#pragma once
/*****************************************************************************
 *
 * Copyright 2016 Varol Okan. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ****************************************************************************/

#include <stdint.h>
#include <string>
#include <map>

#include "mxml/mxml.h"
#include "mpeg/mpeg4_container.h"
#include "mpeg/box.h"
#include "mpeg/constants.h"
#include "mpeg/container.h"

// Utilities for examining/injecting spatial media metadata in MP4/MOV files."""

static const char *MPEG_FILE_EXTENSIONS[2] = { ".mp4", ".mov" };

/*
static const uint8_t SPHERICAL_UUID_ID[] = {0xff, 0xcc, 0x82, 0x63, 0xf8, 0x55, 0x4a, 0x93, 0x88, 0x14, 0x58, 0x7a, 0x02, 0x52, 0x1f, 0xdd };

*/
static const char* SPHERICAL_UUID_ID = "\xff\xcc\x82\x63\xf8\x55\x4a\x93\x88\x14\x58\x7a\x02\x52\x1f\xdd";;

// # XML contents.
static std::string RDF_PREFIX = " xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" ";

static std::string SPHERICAL_XML_HEADER = "<?xml version=\"1.0\"?>"\
"<rdf:SphericalVideo\n"\
"xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"\
"xmlns:GSpherical=\"http://ns.google.com/videos/1.0/spherical/\">";

static std::string SPHERICAL_XML_CONTENTS = "<GSpherical:Spherical>true</GSpherical:Spherical>"\
"<GSpherical:Stitched>true</GSpherical:Stitched>"\
"<GSpherical:StitchingSoftware>"\
"Spherical Metadata Tool"\
"</GSpherical:StitchingSoftware>"\
"<GSpherical:ProjectionType>equirectangular</GSpherical:ProjectionType>";

static std::string SPHERICAL_XML_CONTENTS_TOP_BOTTOM = "<GSpherical:StereoMode>top-bottom</GSpherical:StereoMode>";
static std::string SPHERICAL_XML_CONTENTS_LEFT_RIGHT = "<GSpherical:StereoMode>left-right</GSpherical:StereoMode>";

// Parameter order matches that of the crop option.
static std::string SPHERICAL_XML_CONTENTS_CROP_FORMAT = "<GSpherical:CroppedAreaImageWidthPixels>{0}"\
"</GSpherical:CroppedAreaImageWidthPixels>"\
"<GSpherical:CroppedAreaImageHeightPixels>{1}"\
"</GSpherical:CroppedAreaImageHeightPixels>"\
"<GSpherical:FullPanoWidthPixels>{2}</GSpherical:FullPanoWidthPixels>"\
"<GSpherical:FullPanoHeightPixels>{3}</GSpherical:FullPanoHeightPixels>"\
"<GSpherical:CroppedAreaLeftPixels>{4}</GSpherical:CroppedAreaLeftPixels>"\
"<GSpherical:CroppedAreaTopPixels>{5}</GSpherical:CroppedAreaTopPixels>";

static std::string SPHERICAL_XML_FOOTER = "</rdf:SphericalVideo>";

static const char *SPHERICAL_TAGS_LIST[] = {
    "Spherical",
    "Stitched",
    "StitchingSoftware",
    "ProjectionType",
    "SourceCount",
    "StereoMode",
    "InitialViewHeadingDegrees",
    "InitialViewPitchDegrees",
    "InitialViewRollDegrees",
    "Timestamp",
    "CroppedAreaImageWidthPixels",
    "CroppedAreaImageHeightPixels",
    "FullPanoWidthPixels",
    "FullPanoHeightPixels",
    "CroppedAreaLeftPixels",
    "CroppedAreaTopPixels",
};

static std::string SPHERICAL_PREFIX = "{http://ns.google.com/videos/1.0/spherical/}";

struct SPATIAL_AUDIO_DEFAULT_METADATA {
    SPATIAL_AUDIO_DEFAULT_METADATA ( )  {
        ambisonic_order = 1;
        ambisonic_type  = "periphonic";
        ambisonic_channel_ordering = "ACN";
        ambisonic_normalization    = "SN3D";
        for ( uint32_t t=0; t<4; t++ )
            channel_map[t] = t;
    };
    uint32_t ambisonic_order;
    std::string ambisonic_type;
    std::string ambisonic_channel_ordering;
    std::string ambisonic_normalization;
    uint32_t channel_map[4];
} static PATIAL_AUDIO_DEFAULT_METADATA;


int  inject_metadata(char* src, char*  dest, const char* codeerr);
int  get_fmt_and_inf(char* src,char *fmt,char *inf);
