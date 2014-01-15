//: Begin of link.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "backtrace.h"

#ifndef TRUE
	#define TRUE 1
#endif

#ifndef FALSE
	#define FALSE 0
#endif

typedef struct _NodeData {
	int len;
	char* data;
} NodeData;

typedef struct _LinkNode {
	NodeData* pData;
	struct _LinkNode* pPrev;
	struct _LinkNode* pNext;
} LinkNode;

LinkNode* initLinkNode(void);
LinkNode* initLinkNodeEx(char* data, int len);
NodeData* initLinkData(char* data, int len);
LinkNode* addNode(LinkNode* pNode, LinkNode* pNewNode);
LinkNode* deleteNode(LinkNode* pNode);
int isEmpty(LinkNode *pHead);
int getLength(LinkNode *pHead);
void traverseLinkList(LinkNode *pHead);

static void _deleteNode(LinkNode* pNode)
{
	if (NULL == pNode) {
		return;
	}

	NodeData* pNodeData = pNode->pData;
	free(pNodeData->data);

	free(pNodeData->data);
	pNode->pData = NULL;
	free(pNode);
}

static void showNode(LinkNode* pNode) 
{
	if (NULL == pNode) {
		return;
	}

	NodeData* pData = pNode->pData;

	if (pData == NULL) {
		printf("Node=NULL.\n");
	} else {
		printf("Node[%d]=%s.\n", pData->len, pData->data);
	}
}

LinkNode* initLinkNode(void)
{
	LinkNode* pNode = (LinkNode*) malloc(sizeof(LinkNode));
	if (pNode == NULL) {
		return NULL;
	}

	pNode->pData = NULL;
	pNode->pPrev = NULL;
	pNode->pNext = NULL;

	return pNode;
}

LinkNode* initLinkNodeEx(char* data, int len)
{
	if (data == NULL || len <= 0) {
		return NULL;
	}

	LinkNode* pNode = initLinkNode();	
	if (NULL == pNode) {
		return NULL;
	}

	pNode->pData = initLinkData(data, len);

	return pNode;
}

NodeData* initLinkData(char* data, int len)
{
	if (data == NULL || len <= 0) {
		return NULL;
	}

	NodeData* pData = (NodeData*) malloc(sizeof(NodeData));
	if (NULL == pData) {
		return NULL;
	}

	pData->data = (char*) malloc(len);
	if (NULL == pData->data) {
		free(pData);

		return NULL;
	}

	memcpy(pData->data, data, len);
	pData->len = len;

	return pData;
}

LinkNode* addNode(LinkNode* pNode, LinkNode* pNewNode)
{
	if (NULL == pNode || NULL == pNewNode) {
		return pNode;
	}

	pNode->pNext = pNewNode;
	pNewNode->pPrev = pNode;

	return pNode;
}

LinkNode* deleteNode(LinkNode* pNode)
{
	if (NULL == pNode) {
		return pNode;
	}

	LinkNode* pPrev = pNode->pPrev;
	LinkNode* pNext = pNode->pNext;

	if (pNext == NULL) {
		return pNode;
	}

	pPrev->pNext = pNext;
	pNext->pPrev = pPrev;

	_deleteNode(pNode);

	return pNext;
}

int isEmpty(LinkNode *pHead)
{
	if (NULL == pHead) {
		return TRUE;
	}

	if (NULL == pHead->pPrev && NULL == pHead->pNext) {
		return TRUE;
	} else {
		return FALSE;
	}
}

int getLength(LinkNode *pHead)
{
	if (NULL == pHead) {
		return 0;
	}

	int len = 0;
	LinkNode* pNode = NULL;

	do {
		pNode = pHead->pNext;
		len++;
	} while (pNode != NULL);

	return len;
}

void traverseLinkList(LinkNode *pHead)
{
	if (NULL == pHead) {
		return;
	}

	LinkNode *pNode = pHead->pNext;
	NodeData *pData = NULL; 
	while (NULL != pNode) {
		pData = pNode->pData;		
		if (NULL == pData) {
			printf("Node=NULL.\n");
		} else {
			printf("Node[%d]=%s.\n", pData->len, pData->data);
		}

		pNode = pNode->pNext;
	}

	return;
}

int main(int argc, char* argv[])
{
	REG_DEBUG_SIGNAL;

	LinkNode* pHead = initLinkNode();
	if (NULL == pHead) {
		printf("initLink failed.\n");

		return -1;
	}

	pHead->pData = initLinkData("Hello World", 11);

	showNode(pHead);

	LinkNode* p2 = initLinkNodeEx("Hello", 5);
	addNode(pHead, p2);

	showNode(p2);

	deleteNode(p2);
	deleteNode(pHead);

	return 0;
}

//: ~ End of link.c
