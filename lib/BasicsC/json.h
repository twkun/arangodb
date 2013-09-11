////////////////////////////////////////////////////////////////////////////////
/// @brief json objects
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2004-2013 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Dr. Frank Celler
/// @author Copyright 2011-2013, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef TRIAGENS_BASICS_C_JSON_H
#define TRIAGENS_BASICS_C_JSON_H 1

#include "BasicsC/common.h"

#include "BasicsC/associative.h"
#include "BasicsC/vector.h"

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// --SECTION--                                              forward declarations
// -----------------------------------------------------------------------------

struct TRI_string_buffer_s;

// -----------------------------------------------------------------------------
// --SECTION--                                                              JSON
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// --SECTION--                                                      public types
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Json
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief json type
////////////////////////////////////////////////////////////////////////////////

typedef enum {
  TRI_JSON_UNUSED = 0,
  TRI_JSON_NULL = 1,
  TRI_JSON_BOOLEAN = 2,
  TRI_JSON_NUMBER = 3,
  TRI_JSON_STRING = 4,
  TRI_JSON_STRING_REFERENCE = 5,
  TRI_JSON_ARRAY = 6,
  TRI_JSON_LIST = 7
}
TRI_json_type_e;

////////////////////////////////////////////////////////////////////////////////
/// @brief json object
////////////////////////////////////////////////////////////////////////////////

typedef struct TRI_json_s {
  TRI_json_type_e _type;

  union {
    bool _boolean;
    double _number;
    TRI_blob_t _string;
    TRI_vector_t _objects;
  }
  _value;
}
TRI_json_t;

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                      constructors and destructors
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Json
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a null object
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CreateNullJson (TRI_memory_zone_t*);

////////////////////////////////////////////////////////////////////////////////
/// @brief initialises a null object
////////////////////////////////////////////////////////////////////////////////

void TRI_InitNullJson (TRI_json_t*);

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a boolean object
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CreateBooleanJson (TRI_memory_zone_t*, bool);

////////////////////////////////////////////////////////////////////////////////
/// @brief initialises a boolean object
////////////////////////////////////////////////////////////////////////////////

void TRI_InitBooleanJson (TRI_json_t*, bool);

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a number object
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CreateNumberJson (TRI_memory_zone_t*, double);

////////////////////////////////////////////////////////////////////////////////
/// @brief initialises a number object
////////////////////////////////////////////////////////////////////////////////

void TRI_InitNumberJson (TRI_json_t*, double);

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a string object
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CreateStringJson (TRI_memory_zone_t*, char*);

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a string object with given length
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CreateString2Json (TRI_memory_zone_t*, char* value, size_t length);

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a string object, copying the string
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CreateStringCopyJson (TRI_memory_zone_t*, char const* value);

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a string object with given length, copying the string
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CreateString2CopyJson (TRI_memory_zone_t*, char const*, size_t);

////////////////////////////////////////////////////////////////////////////////
/// @brief initialises a string object
////////////////////////////////////////////////////////////////////////////////

void TRI_InitStringJson (TRI_json_t*, char*);

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a string object
////////////////////////////////////////////////////////////////////////////////

void TRI_InitString2Json (TRI_json_t*, char*, size_t);

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a string reference object
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CreateStringReferenceJson (TRI_memory_zone_t*, const char*);

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a string reference object with given length
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CreateStringReference2Json (TRI_memory_zone_t*, const char* value, size_t length);

////////////////////////////////////////////////////////////////////////////////
/// @brief initialises a string reference object
////////////////////////////////////////////////////////////////////////////////

void TRI_InitStringReferenceJson (TRI_json_t*, const char*);

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a string reference object
////////////////////////////////////////////////////////////////////////////////

void TRI_InitStringReference2Json (TRI_json_t*, const char*, size_t);

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a list object
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CreateListJson (TRI_memory_zone_t*);

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a list object, with the specified initial size
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CreateList2Json (TRI_memory_zone_t*, const size_t);

////////////////////////////////////////////////////////////////////////////////
/// @brief initialises a list object
////////////////////////////////////////////////////////////////////////////////

void TRI_InitListJson (TRI_memory_zone_t*, TRI_json_t*);

////////////////////////////////////////////////////////////////////////////////
/// @brief initialises a list object with a given size
////////////////////////////////////////////////////////////////////////////////

void TRI_InitList2Json (TRI_memory_zone_t*, TRI_json_t*, size_t);

////////////////////////////////////////////////////////////////////////////////
/// @brief creates an array
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CreateArrayJson (TRI_memory_zone_t*);

////////////////////////////////////////////////////////////////////////////////
/// @brief creates an array
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CreateArray2Json (TRI_memory_zone_t*, const size_t);

////////////////////////////////////////////////////////////////////////////////
/// @brief initialises an array
////////////////////////////////////////////////////////////////////////////////

void TRI_InitArrayJson (TRI_memory_zone_t*, TRI_json_t*);

////////////////////////////////////////////////////////////////////////////////
/// @brief initialises an array, using a specific initial size
////////////////////////////////////////////////////////////////////////////////

void TRI_InitArray2Json (TRI_memory_zone_t*, TRI_json_t*, size_t);

////////////////////////////////////////////////////////////////////////////////
/// @brief destroys a json object, but does not free the pointer
////////////////////////////////////////////////////////////////////////////////

void TRI_DestroyJson (TRI_memory_zone_t*, TRI_json_t*);

////////////////////////////////////////////////////////////////////////////////
/// @brief destroys a json object and frees the pointer
////////////////////////////////////////////////////////////////////////////////

void TRI_FreeJson (TRI_memory_zone_t*, TRI_json_t*);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                  public functions
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Json
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief determines whether the JSON passed is of type array
////////////////////////////////////////////////////////////////////////////////

bool TRI_IsArrayJson (TRI_json_t const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief determines whether the JSON passed is of type list
////////////////////////////////////////////////////////////////////////////////

bool TRI_IsListJson (TRI_json_t const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief determines whether the JSON passed is of type string
////////////////////////////////////////////////////////////////////////////////

bool TRI_IsStringJson (TRI_json_t const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief determines whether the JSON passed is of type number
////////////////////////////////////////////////////////////////////////////////

bool TRI_IsNumberJson (TRI_json_t const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief determines whether the JSON passed is of type boolean
////////////////////////////////////////////////////////////////////////////////

bool TRI_IsBooleanJson (TRI_json_t const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief adds a new sub-object to a list object, copying it
////////////////////////////////////////////////////////////////////////////////

void TRI_PushBackListJson (TRI_memory_zone_t*, TRI_json_t* list, TRI_json_t* object);

////////////////////////////////////////////////////////////////////////////////
/// @brief adds a new sub-object to a list object, not copying it
////////////////////////////////////////////////////////////////////////////////

int TRI_PushBack2ListJson (TRI_json_t* list, TRI_json_t* object);

////////////////////////////////////////////////////////////////////////////////
/// @brief adds a new sub-object, not copying it but freeing the pointer
////////////////////////////////////////////////////////////////////////////////

int TRI_PushBack3ListJson (TRI_memory_zone_t*, TRI_json_t* list, TRI_json_t* object);

////////////////////////////////////////////////////////////////////////////////
/// @brief looks up a value in a json list
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_LookupListJson (const TRI_json_t* const , const size_t);

////////////////////////////////////////////////////////////////////////////////
/// @brief adds a new attribute to an object, using copy
////////////////////////////////////////////////////////////////////////////////

void TRI_InsertArrayJson (TRI_memory_zone_t*, TRI_json_t* object, char const* name, TRI_json_t* subobject);

////////////////////////////////////////////////////////////////////////////////
/// @brief adds a new attribute  to an object, not copying it
////////////////////////////////////////////////////////////////////////////////

void TRI_Insert2ArrayJson (TRI_memory_zone_t*, TRI_json_t* object, char const* name, TRI_json_t* subobject);

////////////////////////////////////////////////////////////////////////////////
/// @brief adds a new attribute, not copying it but freeing the pointer
////////////////////////////////////////////////////////////////////////////////

void TRI_Insert3ArrayJson (TRI_memory_zone_t*, TRI_json_t* object, char const* name, TRI_json_t* subobject);

////////////////////////////////////////////////////////////////////////////////
/// @brief adds a new attribute, not copying it but freeing the pointer
///
/// the JSON struct created takes ownership of the name* passed
////////////////////////////////////////////////////////////////////////////////

void TRI_Insert4ArrayJson (TRI_memory_zone_t* zone, TRI_json_t* object, char* name, size_t nameLength, TRI_json_t* subobject, bool);

////////////////////////////////////////////////////////////////////////////////
/// @brief looks up an attribute in a json array
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_LookupArrayJson (const TRI_json_t* const object, char const* name);

////////////////////////////////////////////////////////////////////////////////
/// @brief deletes an element from a json array
////////////////////////////////////////////////////////////////////////////////

bool TRI_DeleteArrayJson (TRI_memory_zone_t* zone, TRI_json_t* object, char const* name);

////////////////////////////////////////////////////////////////////////////////
/// @brief replaces an element in a json array
////////////////////////////////////////////////////////////////////////////////

bool TRI_ReplaceArrayJson (TRI_memory_zone_t* zone, TRI_json_t* object, char const* name, TRI_json_t* replacement);

////////////////////////////////////////////////////////////////////////////////
/// @brief stringifies a json object
////////////////////////////////////////////////////////////////////////////////

int TRI_StringifyJson (struct TRI_string_buffer_s*, TRI_json_t const* object);

////////////////////////////////////////////////////////////////////////////////
/// @brief stringifies a json object skiping the outer braces
////////////////////////////////////////////////////////////////////////////////

int TRI_Stringify2Json (struct TRI_string_buffer_s*, TRI_json_t const* object);

////////////////////////////////////////////////////////////////////////////////
/// @brief prints a json object
////////////////////////////////////////////////////////////////////////////////

bool TRI_PrintJson (int fd, TRI_json_t const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief saves a json object
////////////////////////////////////////////////////////////////////////////////

bool TRI_SaveJson (char const*, TRI_json_t const*, const bool);

////////////////////////////////////////////////////////////////////////////////
/// @brief copies a json object into a given buffer
////////////////////////////////////////////////////////////////////////////////

int TRI_CopyToJson (TRI_memory_zone_t*, TRI_json_t* dst, TRI_json_t const* src);

////////////////////////////////////////////////////////////////////////////////
/// @brief copies a json object
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CopyJson (TRI_memory_zone_t*, const TRI_json_t* const);

////////////////////////////////////////////////////////////////////////////////
/// @brief parses a json string
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_JsonString (TRI_memory_zone_t*, char const* text);

////////////////////////////////////////////////////////////////////////////////
/// @brief parses a json string and returns error message
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_Json2String (TRI_memory_zone_t*, char const* text, char** error);

////////////////////////////////////////////////////////////////////////////////
/// @brief parses a json file and returns error message
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_JsonFile (TRI_memory_zone_t*, char const* path, char** error);

////////////////////////////////////////////////////////////////////////////////
/// @brief determines whether or not two json objects are equal
////////////////////////////////////////////////////////////////////////////////

bool TRI_EqualJsonJson (TRI_json_t*, TRI_json_t*);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#endif

// Local Variables:
// mode: outline-minor
// outline-regexp: "/// @brief\\|/// {@inheritDoc}\\|/// @addtogroup\\|/// @page\\|// --SECTION--\\|/// @\\}"
// End:
