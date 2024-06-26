#ifndef LMTEXNODE_H
#define LMTEXNODE_H

class LMTexNode
{
	
private:

	int iStartU, iStartV, iSizeU, iSizeV;
	bool bFilled;
	bool bFinalised;
	
	LMTexNode *pLeftNode, *pRightNode;

public:

	LMTexNode( );
	LMTexNode( int startU, int startV, int sizeU, int sizeV );
	~LMTexNode( );

	int GetStartU( );
	int GetStartV( );

	void Finalise( );
	bool IsFinalised( );

	LMTexNode* AddImage( int width, int height );
};

#endif