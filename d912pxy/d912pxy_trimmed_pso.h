/*
MIT License

Copyright(c) 2018-2020 megai2

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
#pragma once
#include "stdafx.h"

typedef UINT32 d912pxy_trimmed_pso_desc_hash;

#pragma pack(push, 1)

class d912pxy_trimmed_pso_desc 
{
public:
	struct rt_blend_desc 
	{
		UINT8 enable;
		UINT8 src;
		UINT8 dest;
		UINT8 op;
		UINT8 srcAlpha;
		UINT8 destAlpha;
		UINT8 opAlpha;
		UINT8 writeMask;
	};

	struct rasterizer_desc 
	{
		UINT8 fillMode;
		UINT8 cullMode;
		INT depthBias;
		FLOAT slopeScaledDepthBias;
		UINT8 antialiasedLineEnable;
	};

	struct stencil_op_desc 
	{
		UINT8 failOp;
		UINT8 depthFailOp;
		UINT8 passOp;
		UINT8 func;
	};

	struct ds_desc 
	{
		UINT8 enable;
		UINT8 writeMask;
		UINT8 func;
		UINT8 stencilEnable;
		UINT8 stencilReadMask;
		UINT8 stencilWriteMask;
		UINT8 format;
		stencil_op_desc frontFace;
		stencil_op_desc backFace;
	};

	struct rt_desc {
		rt_blend_desc blend;
		UINT8 format;
	};
	   
	struct value_part {
		UINT vdeclHash;
		rasterizer_desc rast;
		ds_desc ds;
		rt_desc rt0;
		UINT8 NumRenderTargets;
	};

	struct ref_part {
		d912pxy_shader* VS;
		d912pxy_shader* PS;
		d912pxy_vdecl* InputLayout;
	};

	struct serialized_data {
		D3DVERTEXELEMENT9 declData[PXY_INNER_MAX_VDECL_LEN];
		value_part val;
	};

	value_part val;
	ref_part ref;

	static ID3D12RootSignature* defaultRootSignature;

	d912pxy_trimmed_pso_desc();
	~d912pxy_trimmed_pso_desc();
	
	d912pxy_trimmed_pso_desc_hash GetHash();	 
	D3D12_GRAPHICS_PIPELINE_STATE_DESC GetPSODesc();
	d912pxy_shader_pair_hash_type GetShaderPairUID();

	void HoldRefs(const bool yes);
	bool haveValidRefs();

	d912pxy_mem_block Serialize();
	void DeSerialize(d912pxy_mem_block data);

private:
	const D3D12_GRAPHICS_PIPELINE_STATE_DESC GetBaseFullPSO();
};

#pragma pack(pop)