#ifndef _H_MOUSE_
#define _H_MOUSE_

#include "Common.h"

#define AGK_MOUSE_LEFT			0x00000001
#define AGK_MOUSE_RIGHT			0x00000002
#define AGK_MOUSE_MIDDLE		0x00000004
#define AGK_MOUSE_PREV_LEFT		0x00000008
#define AGK_MOUSE_PREV_RIGHT	0x00000010
#define AGK_MOUSE_PREV_MIDDLE	0x00000020
#define AGK_MOUSE_CAPTURED		0x00000040
#define AGK_MOUSE_FOURTH		0x00000080
#define AGK_MOUSE_FIFTH			0x00000100
#define AGK_MOUSE_PREV_FOURTH	0x00000200
#define AGK_MOUSE_PREV_FIFTH	0x00000400

namespace AGK
{
	class cVirtualJoystick;
	class cVirtualButton;

	class _EXPORT_ cMouse
	{
		protected:
			friend class cVirtualJoystick;
			friend class cVirtualButton;

			float m_fX;
			float m_fY;
			float m_fWheelPrev;
			float m_fWheel;
			unsigned int m_bFlags;

			bool GetLeftTrue() 
			{
				return (m_bFlags & AGK_MOUSE_LEFT) != 0; 
			}

			bool GetMiddleTrue() 
			{
				return (m_bFlags & AGK_MOUSE_MIDDLE) != 0; 
			}
			
			bool GetRightTrue() 
			{
				return (m_bFlags & AGK_MOUSE_RIGHT) != 0; 
			}

			bool GetFourthTrue() 
			{
				return (m_bFlags & AGK_MOUSE_FOURTH) != 0; 
			}

			bool GetFifthTrue() 
			{
				return (m_bFlags & AGK_MOUSE_FIFTH) != 0; 
			}

		public:
			cMouse() { m_fX = 0; m_fY = 0; m_fWheel = 0; m_fWheelPrev = 0; m_bFlags = 0; }
			~cMouse() {};

			void Reset() { m_fX = 0; m_fY = 0; m_fWheel = 0; m_fWheelPrev = 0; m_bFlags = 0; }

			void SetPosition( float x, float y )
			{
				m_fX = x;
				m_fY = y;
			}

			void CaptureMouse( )
			{
				m_bFlags |= AGK_MOUSE_CAPTURED;
			}

			void ReleaseMouse( )
			{
				m_bFlags &= ~AGK_MOUSE_CAPTURED;
			}

			void SetButton( int button, int state )
			{
				switch( button )
				{
					case 0: 
					{
						// record new state
						if ( state == 0 )
						{
							ReleaseMouse();
							m_bFlags &= ~AGK_MOUSE_LEFT; 
						}
						else
						{
							m_bFlags |= AGK_MOUSE_LEFT;
						}
						break;
					}
					case 1: 
					{
						// record new state
						if ( state == 0 )
						{
							m_bFlags &= ~AGK_MOUSE_RIGHT; 
						}
						else
						{
							m_bFlags |= AGK_MOUSE_RIGHT;
						}
						break;
					}
					case 2: 
					{
						// record new state
						if ( state == 0 )
						{
							m_bFlags &= ~AGK_MOUSE_MIDDLE; 
						}
						else
						{
							m_bFlags |= AGK_MOUSE_MIDDLE;
						}
						break;
					}
					case 3: 
					{
						// record new state
						if ( state == 0 )
						{
							m_bFlags &= ~AGK_MOUSE_FOURTH; 
						}
						else
						{
							m_bFlags |= AGK_MOUSE_FOURTH;
						}
						break;
					}
					case 4: 
					{
						// record new state
						if ( state == 0 )
						{
							m_bFlags &= ~AGK_MOUSE_FIFTH; 
						}
						else
						{
							m_bFlags |= AGK_MOUSE_FIFTH;
						}
						break;
					}
				}
			}

			void SetWheel( float w ) { m_fWheel = w; }
			void MoveWheel( float w ) { m_fWheel += w; }

			void Update()
			{
				if ( m_bFlags & AGK_MOUSE_LEFT ) m_bFlags |= AGK_MOUSE_PREV_LEFT;
				else m_bFlags &= ~AGK_MOUSE_PREV_LEFT;

				if ( m_bFlags & AGK_MOUSE_RIGHT ) m_bFlags |= AGK_MOUSE_PREV_RIGHT;
				else m_bFlags &= ~AGK_MOUSE_PREV_RIGHT;

				if ( m_bFlags & AGK_MOUSE_MIDDLE ) m_bFlags |= AGK_MOUSE_PREV_MIDDLE;
				else m_bFlags &= ~AGK_MOUSE_PREV_MIDDLE;

				if ( m_bFlags & AGK_MOUSE_FOURTH ) m_bFlags |= AGK_MOUSE_PREV_FOURTH;
				else m_bFlags &= ~AGK_MOUSE_PREV_FOURTH;

				if ( m_bFlags & AGK_MOUSE_FIFTH ) m_bFlags |= AGK_MOUSE_PREV_FIFTH;
				else m_bFlags &= ~AGK_MOUSE_PREV_FIFTH;

				m_fWheelPrev = m_fWheel;
			}

			float GetX() { return m_fX; }
			float GetY() { return m_fY; }
			float GetWheel() { return m_fWheel; }
			float GetWheelDelta() { return m_fWheel-m_fWheelPrev; }

			bool GetLeftPressed() 
			{
				if ( (m_bFlags & AGK_MOUSE_CAPTURED) != 0 ) return false;
				return ( (m_bFlags & AGK_MOUSE_PREV_LEFT) == 0 && (m_bFlags & AGK_MOUSE_LEFT) != 0 ); 
			}

			bool GetLeftState() 
			{
				if ( (m_bFlags & AGK_MOUSE_CAPTURED) != 0 ) return false;
				return (m_bFlags & AGK_MOUSE_LEFT) != 0; 
			}

			bool GetLeftReleased() 
			{
				if ( (m_bFlags & AGK_MOUSE_CAPTURED) != 0 ) return false;
				return ( (m_bFlags & AGK_MOUSE_PREV_LEFT) != 0 && (m_bFlags & AGK_MOUSE_LEFT) == 0 ); 
			}

			bool GetRightPressed() 
			{
				if ( (m_bFlags & AGK_MOUSE_CAPTURED) != 0 ) return false;
				return ( (m_bFlags & AGK_MOUSE_PREV_RIGHT) == 0 && (m_bFlags & AGK_MOUSE_RIGHT) != 0 ); 
			}
			
			bool GetRightState() 
			{
				if ( (m_bFlags & AGK_MOUSE_CAPTURED) != 0 ) return false;
				return (m_bFlags & AGK_MOUSE_RIGHT) != 0; 
			}

			bool GetRightReleased() 
			{
				if ( (m_bFlags & AGK_MOUSE_CAPTURED) != 0 ) return false;
				return ( (m_bFlags & AGK_MOUSE_PREV_RIGHT) != 0 && (m_bFlags & AGK_MOUSE_RIGHT) == 0 ); 
			}

			bool GetMiddlePressed() 
			{
				if ( (m_bFlags & AGK_MOUSE_CAPTURED) != 0 ) return false;
				return ( (m_bFlags & AGK_MOUSE_PREV_MIDDLE) == 0 && (m_bFlags & AGK_MOUSE_MIDDLE) != 0 ); 
			}
			
			bool GetMiddleState() 
			{
				if ( (m_bFlags & AGK_MOUSE_CAPTURED) != 0 ) return false;
				return (m_bFlags & AGK_MOUSE_MIDDLE) != 0; 
			}

			bool GetMiddleReleased() 
			{
				if ( (m_bFlags & AGK_MOUSE_CAPTURED) != 0 ) return false;
				return ( (m_bFlags & AGK_MOUSE_PREV_MIDDLE) != 0 && (m_bFlags & AGK_MOUSE_MIDDLE) == 0 ); 
			}

			bool GetFourthPressed() 
			{
				if ( (m_bFlags & AGK_MOUSE_CAPTURED) != 0 ) return false;
				return ( (m_bFlags & AGK_MOUSE_PREV_FOURTH) == 0 && (m_bFlags & AGK_MOUSE_FOURTH) != 0 ); 
			}
			
			bool GetFourthState() 
			{
				if ( (m_bFlags & AGK_MOUSE_CAPTURED) != 0 ) return false;
				return (m_bFlags & AGK_MOUSE_FOURTH) != 0; 
			}

			bool GetFourthReleased() 
			{
				if ( (m_bFlags & AGK_MOUSE_CAPTURED) != 0 ) return false;
				return ( (m_bFlags & AGK_MOUSE_PREV_FOURTH) != 0 && (m_bFlags & AGK_MOUSE_FOURTH) == 0 ); 
			}

			bool GetFifthPressed() 
			{
				if ( (m_bFlags & AGK_MOUSE_CAPTURED) != 0 ) return false;
				return ( (m_bFlags & AGK_MOUSE_PREV_FIFTH) == 0 && (m_bFlags & AGK_MOUSE_FIFTH) != 0 ); 
			}
			
			bool GetFifthState() 
			{
				if ( (m_bFlags & AGK_MOUSE_CAPTURED) != 0 ) return false;
				return (m_bFlags & AGK_MOUSE_FIFTH) != 0; 
			}

			bool GetFifthReleased() 
			{
				if ( (m_bFlags & AGK_MOUSE_CAPTURED) != 0 ) return false;
				return ( (m_bFlags & AGK_MOUSE_PREV_FIFTH) != 0 && (m_bFlags & AGK_MOUSE_FIFTH) == 0 ); 
			}

			bool IsCaptured() { return (m_bFlags & AGK_MOUSE_CAPTURED) != 0; }
	};
}

#endif