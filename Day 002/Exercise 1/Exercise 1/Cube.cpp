//=======================================================================================
// Cube.cpp                                                                         
//=======================================================================================

#include "Cube.h"
#include "Vertex.h"
#include <vector>

Cube::Cube()
: mNumRows(0), mNumCols(0), mNumVertices(0), mNumFaces(0),
  md3dDevice(0), mVB(0), mIB(0)
{
}


Cube::~Cube()
{
	ReleaseCOM(mVB);
	ReleaseCOM(mIB);
}



void Cube::init(ID3D10Device* device, float scale)
{
	md3dDevice = device;

	mNumVertices = 24;
	mNumFaces    = 12; // 2 per quad

	// Create vertex buffer
	Vertex vertices[] =
	{
		// Front
		{ D3DXVECTOR3( -1.0f, 1.0f, -1.0f ), RED },
		{ D3DXVECTOR3( 1.0f, 1.0f, -1.0f ), RED },
		{ D3DXVECTOR3( 1.0f, -1.0f, -1.0f), RED },
		{ D3DXVECTOR3( -1.0f, -1.0f, -1.0f), RED },

		// Left
		{ D3DXVECTOR3(-1.0f, 1.0f, 1.0f), CYAN },
		{ D3DXVECTOR3(-1.0f, 1.0f, -1.0f), CYAN },
		{ D3DXVECTOR3(-1.0f, -1.0f, -1.0f), CYAN },
		{ D3DXVECTOR3(-1.0f, -1.0f, 1.0f), CYAN },
		
		// Right
		{ D3DXVECTOR3(1.0f, 1.0f, -1.0f), GREEN },
		{ D3DXVECTOR3(1.0f, 1.0f, 1.0f), GREEN },
		{ D3DXVECTOR3(1.0f, -1.0f, 1.0f), GREEN },
		{ D3DXVECTOR3(1.0f, -1.0f, -1.0f), GREEN },
		
		// Back
		{ D3DXVECTOR3(1.0f, 1.0f, 1.0f), MAGENTA },
		{ D3DXVECTOR3(-1.0f, 1.0f, 1.0f), MAGENTA },
		{ D3DXVECTOR3(-1.0f, -1.0f, 1.0f), MAGENTA },
		{ D3DXVECTOR3(1.0f, -1.0f, 1.0f), MAGENTA },
		
		// Top
		{ D3DXVECTOR3(-1.0f, 1.0f, 1.0f), YELLOW },
		{ D3DXVECTOR3(1.0f, 1.0f, 1.0f), YELLOW },
		{ D3DXVECTOR3(1.0f, 1.0f, -1.0f), YELLOW },
		{ D3DXVECTOR3(-1.0f, 1.0f, -1.0f), YELLOW },
		
		// Bottom
		{ D3DXVECTOR3(-1.0f, -1.0f, -1.0f), DARKBROWN },
		{ D3DXVECTOR3(1.0f, -1.0f, -1.0f), DARKBROWN },
		{ D3DXVECTOR3(1.0f, -1.0f, 1.0f), DARKBROWN },
		{ D3DXVECTOR3(-1.0f, -1.0f, 1.0f), DARKBROWN }
	};

	// Scale the box.
	for(DWORD i = 0; i < mNumVertices; ++i)
		vertices[i].pos *= scale;


	D3D10_BUFFER_DESC vbd;
	vbd.Usage = D3D10_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * mNumVertices;
	vbd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D10_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertices;
	HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &mVB));


	// Create the index buffer

	DWORD indices[] = {
		// Front Face
		0, 1, 2,
		0, 2, 3,

		// Left Face
		4, 5, 6,
		4, 6, 7,

		// Right Face
		8, 9, 10,
		8, 10, 11,

		// Back Face
		12, 13, 14,
		12, 14, 15,

		// Top Face
		16, 17, 18,
		16, 18, 19,

		// Bottom Face
		20, 21, 22,
		20, 22, 23
	};

	D3D10_BUFFER_DESC ibd;
	ibd.Usage = D3D10_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(DWORD) * mNumFaces*3;
	ibd.BindFlags = D3D10_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D10_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices;
	HR(md3dDevice->CreateBuffer(&ibd, &iinitData, &mIB));

	rotationPitch = 0;
	rotationYaw = 0;
	rotationRoll = 0;
}

void Cube::update(float dt)
{
	rotationPitch += 0.01;
	rotationRoll += 0.01;

	D3DXMATRIX matRotationX;
	D3DXMATRIX matRotationY;
	D3DXMATRIX matRotationZ;
	D3DXMatrixRotationX(&matRotationX, D3DXToRadian(rotationPitch));
	D3DXMatrixRotationY(&matRotationY, D3DXToRadian(rotationYaw));
	D3DXMatrixRotationZ(&matRotationZ, D3DXToRadian(rotationRoll));

	matRotation = matRotationX * matRotationY * matRotationZ;
}

void Cube::draw()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	md3dDevice->IASetVertexBuffers(0, 1, &mVB, &stride, &offset);
	md3dDevice->IASetIndexBuffer(mIB, DXGI_FORMAT_R32_UINT, 0);
	md3dDevice->DrawIndexed(mNumFaces*3, 0, 0);
}
