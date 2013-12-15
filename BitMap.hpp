#ifndef _BITMAP_HPP_
#define _BITMAP_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BYTESIZE	(8*sizeof(unsigned char))

namespace QQGameServerLib
{
    template<unsigned int uiSize>
    class CBitMap
    {
    public:
        CBitMap();
        ~CBitMap();

        CBitMap<uiSize>& operator =(CBitMap<uiSize>& rExBitMap);
        int	IsBitSetted(unsigned int uiBitSeq);
        int	SetBit(unsigned int uiBitSeq);
        int ClearBit(unsigned int uiBitSeq);
        int ClearAllBits();
        unsigned int GetSettedBits(int *piBitSeqs);
        unsigned int GetSettedCount();
        int GetMapMem(unsigned int& riSize, unsigned char * pbyMap);
		int SetMapMem(unsigned int iSize, unsigned char * pbyMap);
        void Show(FILE *fpOut);

    private:
        unsigned char m_acBitMap[uiSize];
    };

	template<unsigned int uiSize>
	int QQGameServerLib::CBitMap<uiSize>::SetMapMem( unsigned int iSize, unsigned char * pbyMap )
	{
		if (uiSize < iSize)
		{
			iSize = uiSize;
		}
		memcpy((void *)m_acBitMap, (const void *)pbyMap, iSize);
		return 0;
	}

    template<unsigned int uiSize>
    CBitMap<uiSize>::CBitMap()
    {
        
    }

    template<unsigned int uiSize>
    CBitMap<uiSize>::~CBitMap()
    {

    }

    template<unsigned int uiSize>
    CBitMap<uiSize>& CBitMap<uiSize>::operator =(CBitMap<uiSize>& rExBitMap)
    {
        memcpy((void *)m_acBitMap, (const void *)rExBitMap.m_acBitMap, sizeof(m_acBitMap));
        return *this;
    }

    template<unsigned int uiSize>
    int CBitMap<uiSize>::IsBitSetted(unsigned int uiBitSeq)
    {
        int iMapIdx = 0;
        int iBitIdx = 0;
        unsigned char ucTempSMap = 0x80;

        iMapIdx = uiBitSeq / BYTESIZE;
        iBitIdx = uiBitSeq % BYTESIZE;

        if((unsigned int)iMapIdx >= uiSize)
        {
            return 0;
        }

        if( m_acBitMap[iMapIdx] & (ucTempSMap >> iBitIdx) )
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    template<unsigned int uiSize>
    int CBitMap<uiSize>::SetBit(unsigned int uiBitSeq)
    {
        int iMapIdx = 0;
        int iBitIdx = 0;
        unsigned char ucTempSMap = 0x80;

        iMapIdx = uiBitSeq / BYTESIZE;
        iBitIdx = uiBitSeq % BYTESIZE;

        if((unsigned int)iMapIdx >= uiSize)
        {
            return 0;
        }

        m_acBitMap[iMapIdx] |= (ucTempSMap >> iBitIdx);

        return 0;
    }

    template<unsigned int uiSize>
    int CBitMap<uiSize>::ClearBit(unsigned int uiBitSeq)
    {
        int iMapIdx = 0;
        int iBitIdx = 0;
        unsigned char ucTempSMap = 0x80;

        iMapIdx = uiBitSeq / BYTESIZE;
        iBitIdx = uiBitSeq % BYTESIZE;

        if((unsigned int)iMapIdx >= uiSize)
        {
            return 0;
        }

        m_acBitMap[iMapIdx] &= (0xff^(ucTempSMap>>iBitIdx));

        return 0;
    }

    template<unsigned int uiSize>
    int CBitMap<uiSize>::ClearAllBits()
    {
        memset((void *)m_acBitMap, 0, sizeof(m_acBitMap));
        return 0;
    }

    template<unsigned int uiSize>
    unsigned int CBitMap<uiSize>::GetSettedBits(int *piBitSeqs)
    {
        unsigned int uiBitCount; 
        unsigned int i;

        if( !piBitSeqs )
        {
            return -1;
        }
        uiBitCount = 0;

        for( i = 0; i < uiSize*BYTESIZE; i++ )
        {
            if( IsBitSetted(i) )
            {
                piBitSeqs[uiBitCount] = i;
                uiBitCount++;
            }
        }

        return uiBitCount;
    }

    template<unsigned int uiSize>
    unsigned int CBitMap<uiSize>::GetSettedCount()
    {
        unsigned int uiBitCount = 0;
        unsigned int i;

        for(i = 0; i < uiSize*BYTESIZE; i++)
        {
            if( IsBitSetted(i))
            {
                uiBitCount++;
            }
        }

        return uiBitCount;
    }

    template<unsigned int uiSize>
    int CBitMap<uiSize>::GetMapMem(unsigned int& ruiSize, unsigned char *pbyMap)
    {
        ruiSize = uiSize;
        memcpy((void *)pbyMap, (const void *)m_acBitMap, ruiSize);
        return 0;
    }

    template<unsigned int uiSize>
    void CBitMap<uiSize>::Show(FILE *fpOut)
    {

    }
}

#endif

