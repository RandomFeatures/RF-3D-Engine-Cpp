#ifndef _FPSTIMER_H_
#define _FPSTIMER_H_

//To Do:
// - GetFPSString, which is a preformatted string for lazy people


class FPSTimer
{
protected:

   DWORD m_frames_one_second;
   DWORD m_frames;
   DWORD m_min_one_second;
   DWORD m_max_one_second;
   DWORD m_start_time;
   DWORD m_one_second_start_time;

public:
   inline void StartTimer();
   inline void CheckTimer(float *p_fps,DWORD *p_min_1_sec,DWORD *p_max_1_sec);
   inline DWORD GetFPS();

   inline void AfterPresent();

};

//********************************************************************
// Whazzit:Initializes all variables & records current time.  You can
//         safely call this function multiple times, it will just
//         reset the timer.
//********************************************************************
inline void FPSTimer::StartTimer()
{

   m_frames_one_second=0;
   m_frames=0;
   m_min_one_second=0x7fffffff;
   m_max_one_second=0;

   m_start_time=GetTickCount();
   m_one_second_start_time=m_start_time;

}

//      fps_file2 << fps << " " << m_app_name << endl;
//      fps_file2 << m_min_one_second << " min" <<endl;
//      fps_file2 << m_max_one_second << " max" <<endl;

//********************************************************************
// Whazzit:Fills parameters with FPS timings.  This is useful if you'd
//         like to display the FPS on the screen rather than (or in
//         addition to) the log file.
//********************************************************************
inline void FPSTimer::CheckTimer(float *p_fps,DWORD *p_min_1_sec,DWORD *p_max_1_sec)
{

   *p_fps=GetFPS();
   *p_min_1_sec=m_min_one_second;
   *p_max_1_sec=m_max_one_second;

}
//********************************************************************
// Whazzit:Returns average FPS.
//********************************************************************
inline DWORD FPSTimer::GetFPS()
{
DWORD end_time=0,total_time=0;
div_t  fps;

   end_time=GetTickCount();
   total_time=end_time-m_start_time;
   fps=div(m_frames,total_time);

//   fps=((float)m_frames/(float)total_time)*1000.0f;

   return fps.rem;
}
//********************************************************************
// Whazzit:increment the frame counters.
//********************************************************************
inline void FPSTimer::AfterPresent()
{
   m_frames_one_second++;
   m_frames++;


   if((GetTickCount() - m_one_second_start_time) > 1000)
   {
      if(m_frames_one_second < m_min_one_second)
         m_min_one_second=m_frames_one_second;
      if(m_frames_one_second > m_max_one_second)
         m_max_one_second=m_frames_one_second;

      m_frames_one_second=0;

      m_one_second_start_time = GetTickCount();
   }

};



#endif //#ifndef FPSTIMER_H_
