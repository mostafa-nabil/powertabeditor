/////////////////////////////////////////////////////////////////////////////
// Name:            direction.h
// Purpose:         Stores and renders directions
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 9, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#include "powertabobject.h"

#include <vector>

/// Stores and renders directions
class Direction : public PowerTabObject
{
// Constants
public:
    // Default Constants
    static const uint8_t         DEFAULT_POSITION;       ///< Default value for the position member variable
    
    // Position Constants
    static const uint32_t       MIN_POSITION;           ///< Minimum allowed value for the position member variable
    static const uint32_t       MAX_POSITION;           ///< Maximum allowed value for the position member variable

    // Symbol Constants
    static const uint8_t         MAX_SYMBOLS;            ///< Maximum allowed number of symbols in the symbol array
    static const uint8_t         NUM_SYMBOL_TYPES;       ///< Number of direction symbol types
    
    // Repeat Number Constants
    static const uint8_t         MIN_REPEAT_NUMBER;      ///< Minimum allowed value for the repeat number
    static const uint8_t         MAX_REPEAT_NUMBER;      ///< Maximum allowed value for the repeat number

    enum symbolTypes
    {
        coda                            = (uint8_t)0x00,
        doubleCoda                      = (uint8_t)0x01,
        segno                           = (uint8_t)0x02,
        segnoSegno                      = (uint8_t)0x03,
        fine                            = (uint8_t)0x04,
        daCapo                          = (uint8_t)0x05,
        dalSegno                        = (uint8_t)0x06,
        dalSegnoSegno                   = (uint8_t)0x07,
        toCoda                          = (uint8_t)0x08,
        toDoubleCoda                    = (uint8_t)0x09,
        daCapoAlCoda                    = (uint8_t)0x0a,
        daCapoAlDoubleCoda              = (uint8_t)0x0b,
        dalSegnoAlCoda                  = (uint8_t)0x0c,
        dalSegnoAlDoubleCoda            = (uint8_t)0x0d,
        dalSegnoSegnoAlCoda             = (uint8_t)0x0e,
        dalSegnoSegnoAlDoubleCoda       = (uint8_t)0x0f,
        daCapoAlFine                    = (uint8_t)0x10,
        dalSegnoAlFine                  = (uint8_t)0x11,
        dalSegnoSegnoAlFine             = (uint8_t)0x12
    };

    enum activeSymbols
    {
        activeNone                      = (uint8_t)0x00,
        activeDaCapo                    = (uint8_t)0x01,
        activeDalSegno                  = (uint8_t)0x02,
        activeDalSegnoSegno             = (uint8_t)0x03
    };

    enum flags
    {
        symbolTypeMask                  = (uint16_t)0xff00,       ///< Mask used to retrieve the symbol type (coda, segno, etc.)
        activeSymbolMask                = (uint16_t)0xc0,         ///< Mask used to retrieve the active symbol value
        repeatNumberMask                = (uint16_t)0x3f         ///< Mask used to retrieve the repeat number value
    };
    
// Member Variables
private:
    uint8_t                 m_position;         ///< Zero-based index of the position within the system where the direction is anchored
    std::vector<uint16_t>   m_symbolArray;      ///< Array of direction symbols (symbol: top byte = symbol type, next 2 bits = active symbol, next 6 bits = repeat number)

// Constructor/Destructor
public:
    Direction();
    Direction(uint32_t position, uint8_t symbolType, uint8_t activeSymbol,
        uint8_t repeatNumber);
    Direction(const Direction& direction);
    
// Operators
    const Direction& operator=(const Direction& direction);
    bool operator==(const Direction& direction) const;
    bool operator!=(const Direction& direction) const;

// Serialization functions
    bool Serialize(PowerTabOutputStream& stream) const;
    bool Deserialize(PowerTabInputStream& stream, uint16_t version);

// MFC Class Functions
public:
    /// Gets the MFC Class Name for the object
    /// @return The MFC Class Name
    std::string GetMFCClassName() const
    {
        return "CDirection";
    }
    
    /// Gets the MFC Class Schema for the object
    /// @return The MFC Class Schema
    uint16_t GetMFCClassSchema() const                        
    {
        return 1;
    }
    
// Position Functions
    static bool IsValidPosition(uint32_t position);
    bool SetPosition(uint32_t position);
    uint32_t GetPosition() const;
    
    static bool IsValidSymbolType(uint8_t symbolType);
    static bool IsValidActiveSymbol(uint8_t activeSymbol);
    static bool IsValidRepeatNumber(uint8_t repeatNumber);
        
// Symbol Array Functions
    bool IsValidSymbolIndex(uint32_t index) const;
    
    bool AddSymbol(uint8_t symbolType, uint8_t activeSymbol = activeNone,
        uint8_t repeatNumber = 0);
    
    size_t GetSymbolCount() const;
    
    bool SetSymbol(uint32_t index, uint8_t symbolType, uint8_t activeSymbol,
        uint8_t repeatNumber);
    
    bool GetSymbol(uint32_t index, uint8_t& symbolType, uint8_t& activeSymbol,
        uint8_t& repeatNumber) const;
    
    bool IsSymbolType(uint32_t index, uint8_t symbolType) const;
    
    bool RemoveSymbolAtIndex(uint32_t index);
    
    std::string GetText(uint32_t index) const;
};

#endif
