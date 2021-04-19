# Brawlhalla
Simple Brawlhalla Gravity Cancel Scripts
All functions are Game Specific and fairly easy to use if you know in game lingo. 

INPUT DOCUMENTATION:

void sleepyms(int delay): std::this_thread::sleep_for(std::chrono::milliseconds(delay)); sleep in MS
void sleepys(int delay): std::this_thread::sleep_for(std::chrono::seconds(delay)); sleep in Seconds
void accSleep(int ms): accurate sleep using QueryPerformanceCounter, grabbed from GuidedHacking

void KeyUp(WORD vkcode, int rand) Sends keyup on whatever key u input... shocker
void KeyDown(WORD vkey, int rand) I wonder if you can figure it out
void TypeKey(WORD vkey) presses the key down, then up

void leftDown() left mouse down
void leftUp() left mouse up
void LeftC() left mouse click

void rightDown() right mouse down
void rightUp() right mouse up
void RightC() right mouse click

bool pd(int vkcode) checks if whatever key is being pressed

void NeutralLight(int msDelay) sends a neutral light attack
void DownLight(int msDelay) sends a down light attack
void SideLight(int msDelay) sends a side light attack, used to start most combos
void SLight(int msDelay) in-air side light

void NeutralHeavy(int msDelay) neutral heavy or sig attack
void DownHeavy(int msDelay) down sig attack
void SideHeavy(int msDelay) side sig attack

void jump(int msDelay) just presses the W key

void LightGravCancel(int randomshift, int randomlc) does a gravity cancel based on what direction ur facing
void SideLightGravCancel(int randomshift, int randomlc, int msDelay) gravity cancels a light attack in whichever direction ur moving
void NeutralLightGravCancel(int randomshift, int randomlc, int msDelay) neutral light gravity cancel
void DownLightGravCancel(int randomshift, int randomlc, int msDelay) down light gravity cancel

void HeavyGravCancel(int randomshift, int randomlc) does a gravity cancel'd sig in whichever direction ur facing
void SideHeavyGravCancel(int randomshift, int randomlc, int msDelay) side gravity cancel
void NeutralHeavyGravCancel(int randomshift, int randomlc, int msDelay) neutral gravity cancels
void DownHeavyGravCancel(int randomshift, int randomlc, int msDelay) down Gravity Cancels
