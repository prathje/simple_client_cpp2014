/*(c)2013 by Patrick Rathje visit https://github.com/Pata94 and ReadMe for more information
made for Software-Challenge 2013 visit http://www.informatik.uni-kiel.de/software-challenge/  for more information*/
#include "CBaseLogic.h"
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "CGameHandler.h"
#include "CGameState.h"
using namespace std;
CBaseLogic::CBaseLogic(int Player)
{
    m_Player=Player;
    m_pGameState = 0;
    for(int i = 0; i <10; i++)
    {
        m_pBestMoveC[i] = 0;
        m_pOldBestMoveC[i] = 0;
    }
}

CBaseLogic::~CBaseLogic()
{
    //dtor
}

static int num = 0;


int CBaseLogic::GetCardValue(CGameState *pState, CStoneHandler::CStone *pStone)
{
     int points = 0;
     CFieldHandler *pTemp = pState->m_pFieldHandler->Clone();
     pTemp->NewRound(); //delete restrictions
     for(int i = 0; i < FIELD_WIDTH * FIELD_HEIGHT; ++i)
                {
                    int p = pTemp->CanPlace( i, pStone);
                    if(p > 0)
                    {
                        if(p > points)
                            points = p;
                        else
                            points += (int)(p*0.3f);
                    }
                }
    delete pTemp;
    return points;
}

int CBaseLogic::GetHandCardValues(CGameState *pState, int player)
{
    int points = 0;
    for(int i = player*6; i < player*6+6; ++i)
    {
        if(pState->m_apHandStones[i] != 0)
        {
            points += GetCardValue(pState, pState->m_apHandStones[i]);
        }
    }
    return points;
}
void CBaseLogic::OnRequestAction(CGameState::CMoveContainer **ppMoves)
{



    printf("MoveRequest  ");
    CGameState::CMoveContainer *possibleMoves=m_pGameState->GetPossibleMoves(m_Player);

    if(possibleMoves->m_lpMoves.size()==0)
        {
            *ppMoves = new CGameState::CMoveContainer();
            printf("No possible Moves");

           // pMove->m_FieldIndex = i;
            (*ppMoves)->m_MoveType = MOVE_EXCHANGE;
            for(int i = 0; i < 6; ++i)
            {
                CGameState::CMove *pMove = new CGameState::CMove();
                pMove->m_pStone = m_pGameState->m_apHandStones[m_Player*6+i]->Clone();
                pMove->m_Mode = MOVE_EXCHANGE;
                pMove->m_CardIndex = m_Player*6+i;
                (*ppMoves)->m_lpMoves.push_back(pMove);
            }

             delete possibleMoves;
            return;
        }
      if(possibleMoves->m_MoveType == MOVE_PLACE_FIRST)
        {
            *ppMoves = new CGameState::CMoveContainer();
            for(int i = 0; i < possibleMoves->m_lpMoves.size(); ++i)
            {
                  (*ppMoves)->m_MoveType = MOVE_PLACE;
                (*ppMoves)->m_lpMoves.push_back(possibleMoves->m_lpMoves[i]->Clone());
            }
             delete possibleMoves;
            return;
        }

    for(int i= 0; i < 10; i++)
    {
        m_BestPoints[i] = -9999999;
    }
    num = 0;
    CGameState::CMoveContainer *pTemp = new CGameState::CMoveContainer();
    pTemp->m_MoveType = MOVE_PLACE;
    CGameState *pTempState = m_pGameState->Clone();
    TestFunc(pTempState, pTemp);
    for(int i = 0; i < 10; i++)
    {
        m_OldBestPoints[i] = m_BestPoints[i];
        m_pOldBestMoveC[i]  = m_pBestMoveC[i];
        m_pBestMoveC[i] = 0;
    }

    delete pTempState;
    delete pTemp;
    for(int i = 0; i < 10; i++)
    {
        pTemp = new CGameState::CMoveContainer();
        pTemp->m_MoveType = MOVE_PLACE;
        pTempState = m_pGameState->Clone();
        pTempState->DoMove(m_pOldBestMoveC[i]);
        pTempState->EndRound();
        if(pTempState->GetPossibleMoves(pTempState->m_CurrentPlayer) != 0)
        {
            TestFunc(pTempState, pTemp);
            m_OldBestPoints[i] -= m_BestPoints[0]/2;
        }
        delete pTempState;
        delete pTemp;
    }
    m_BestPoints[0] = m_OldBestPoints[0];
    m_pBestMoveC[0] = m_pOldBestMoveC[0];
    for(int i = 0; i < 10; i++)
    {
        if(m_OldBestPoints[i] > m_BestPoints[0])
        {
            delete m_pBestMoveC[0];
            m_BestPoints[0] = m_OldBestPoints[i];
            m_pBestMoveC[0] = m_pOldBestMoveC[i];
            m_pOldBestMoveC[i] = 0;
        }
    }
   /* CGameState::CMove *pTemp = new CGameState::CMove();
    *pTemp = *(pointMoves.front().ppMove);*/
    *ppMoves = m_pBestMoveC[0];
    m_pBestMoveC[0] = 0;
    delete[] m_pBestMoveC;
    delete[] m_pOldBestMoveC;
    delete possibleMoves;

    printf("NUM: %i", num);
  // pMoves->m_MoveType = MOVE_PLACE;
  /* pMoves->m_lpMoves.clear();
   for(int i = 0; i < m_pBestMoveC->m_lpMoves.size(); ++i)
   {
       pMoves->m_lpMoves.push_back(m_pBestMoveC->m_lpMoves[i]->Copy());
   }*/

    //Move muss jetzt nur noch ausgeführt werden
    //sort function needs to be properly implemented
    /*for(int i = 0; i <3; ++i)
    {
        if(possibleMoves.size()==0)
            break;
        srand (time(NULL));
        CGameState::CMove* tempMove = possibleMoves[(rand()%possibleMoves.size())];
        printf("\n Zug: %d, %d",i, m_pGameState->DoMove(tempMove));
         aMoves[i]=tempMove;

    printf("MoveRequest %d \n", m_Player);
    {
        CGameState::CMoveContainer *possibleMoves=m_pGameState->GetPossibleMoves(m_Player);
        if(possibleMoves->m_lpMoves.size()==0)
        {
            printf("No possible Moves");
             CGameState::CMove *pMove = new CGameState::CMove();
            pMove->m_pStone = m_pGameState->m_apHandStones[m_Player*6];
            pMove->m_Mode = MOVE_EXCHANGE;
           // pMove->m_FieldIndex = i;
            pMoves->m_MoveType = MOVE_EXCHANGE;
         pMoves->m_lpMoves.push_back(pMove);
            return;
        }
        if(possibleMoves->m_MoveType == MOVE_PLACE_FIRST)
        {
            for(int i = 0; i < possibleMoves->m_lpMoves.size(); ++i)
            {
                  pMoves->m_MoveType = MOVE_PLACE;
                pMoves->m_lpMoves.push_back(possibleMoves->m_lpMoves[i]);
            }
        }
        else
        {

            srand (time(NULL));
            CGameState::CMove* tempMove = (possibleMoves->m_lpMoves)[(rand()%possibleMoves->m_lpMoves.size())];
            printf("\n Zug:  %d", m_pGameState->DoMove(tempMove));
            pMoves->m_MoveType = MOVE_PLACE;
             pMoves->m_lpMoves.push_back(tempMove);
        }
*/
}

/*CGameState::CMove* CBaseLogic::GetBestMove(CGameState::CMoveContainer *pMoves)
{

}*/
int CBaseLogic::TestGameState(CGameState *pState, CGameState::CMoveContainer* pMoveC)
{

    int points = pMoveC->GetPoints()*7;
   // points -= GetHandCardValues(pState, m_Player == 0 ? 1 : 0);
  /* CGameState *pTemp = pState->Clone();
   pTemp->EndRound();

    for(int i = 0; i < 6; ++i)
    {
        if(pTemp->m_apOpenStones[i] != 0)
            points -= GetCardValue(pTemp, pTemp->m_apOpenStones[i])/(i+1);
    }
    points += GetHandCardValues(pTemp, pState->m_CurrentPlayer)*0.5;*/
    num++;
    return points;
}

void CBaseLogic::TestFunc(CGameState *pState, CGameState::CMoveContainer* pMoveC)
{

      CGameState::CMoveContainer *possibleMoves=pState->GetPossibleMoves(m_Player);
        if(pMoveC->m_lpMoves.size()>0)
        {
            int points = TestGameState(pState, pMoveC);
            for(int i = 0; i < 10; i++)
            {
                if(m_BestPoints[i] < points)
                {
                    delete m_pBestMoveC[9];
                    for(int a = 10-1; a > i; a--)
                    {
                        m_pBestMoveC[a] = m_pBestMoveC[a-1];
                        m_BestPoints[a] = m_BestPoints[a-1];
                    }
                    m_pBestMoveC[i] = pMoveC->Clone();
                    m_BestPoints[i] = points;
                }
            }
        }
        for(int i = 0; i < possibleMoves->m_lpMoves.size(); ++i)
        {
            CGameState::CMove* pTemp = possibleMoves->m_lpMoves[i]->Clone();
            CGameState* pTempState = pState->Clone();
             CGameState::CMoveContainer *ABD = new CGameState::CMoveContainer();

             ABD->m_MoveType = MOVE_PLACE;
             ABD->m_lpMoves.push_back(pTemp);
            pTempState->DoMove(ABD);
            ABD->m_lpMoves.clear();
            delete ABD;

            CGameState::CMoveContainer *pTempContainer = pMoveC->Clone();

            pTempContainer->m_lpMoves.push_back(pTemp);
            TestFunc(pTempState, pTempContainer);
            delete pTempState;
            delete pTempContainer;
        }


    delete possibleMoves;

}
void CBaseLogic::OnGameStateUpdate(CGameState *pNewState)
{
    printf("GameStateUpdate");
    if(m_pGameState == NULL)
        m_pGameState = pNewState;
    else
    {
        delete m_pGameState;
        m_pGameState = pNewState;
    }
   // if(pNewState != NULL)
       // pNewState->CopyGameState(m_pGameState);
}

