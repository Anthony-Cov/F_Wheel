<H1>Fortune Wheel for a doubtful choice</H1>
Draws a spinning silly wheel witn N numbers to choose the lucky one.<BR>
Uses <A href="https://www.sfml-dev.org/download/">SFML 2.6.2</A> for drawing.<BR>
<H3>For Windows</H3>
<B>/F_Wheel</B> folder contains a version compilled for Windows 10 and required font and .dll's.</BR>
Maybe <A href=https://www.dll-files.com/search/?q=libwinpthread-1.dll>  libwinpthread-1.dll </A>,
<A href=https://www.dll-files.com/search/?q=libgcc_s_seh-1.dll> libwinpthread-1.dll </A>, 
<A href=https://www.dll-files.com/libstdc%2B%2B-6.dll.html> libstdc++-6.dll </A> should be added to <B>/F_Wheel</B> folder.
<H3>For Linux</H3>
<B>/F_Wheel_Linux</B> folder contains a version compilled for Ubuntu/Mint and required font. As for libraries if missing run 
 <pre><code>sudo apt-get install libsfml-dev</code></pre>
<I>(Compilled with gcc 13.3.0 on Linux Mint 22 Wilma base: Ubuntu 24.04 noble)</I><BR><BR>
<img src="f_wheel.png" width="500" height="500" >
Save <B>/F_Wheel</B> or <B>/F_Wheel_Linux</B> folder somewhere. Launch <code>>FortuneWheel.exe</code> in command line or <code>$./FortuneWheel</code> in terminal. Put the number of chances (N) from 2 to 36 (zero excluded). 
When the wheel appears click to start spinning.<BR>
<H3>Good luck to all!</H3>

