<p><span style="font-family:Tahoma,Geneva,sans-serif"><span style="font-size:11pt"><strong><span style="font-size:18.0pt">ABOUT</span></strong></span></span></p>

<p><span style="font-family:Tahoma,Geneva,sans-serif"><span style="font-size:11pt">This was my submission for the Ubisoft NEXT programming challenge in 2021, which I finished in the top 5. The challenge was to make a tower defense game in three days with the code framework provided.</span></span></p>

<p><span style="font-family:Tahoma,Geneva,sans-serif"><span style="font-size:11pt">Participants would be able to play audio and render simple 2D line segments and sprites with the base framework.</span></span></p>

<p>&nbsp;</p>

<p><span style="font-family:Tahoma,Geneva,sans-serif"><span style="font-size:11pt"><strong><span style="font-size:18.0pt">HOW TO PLAY</span></strong></span></span></p>

<p><span style="font-family:Tahoma,Geneva,sans-serif"><span style="font-size:11pt"><span style="font-size:12.0pt">The goal is to stop the monsters before they reach the cube in the middle. You achieve this by building towers on their path using your available funds (shown in the top left corner).</span></span></span></p>

<p><span style="font-family:Tahoma,Geneva,sans-serif"><span style="font-size:11pt"><span style="font-size:12.0pt">Click the &ldquo;start&rdquo; button to begin the game. You can then place towers by clicking the buttons onscreen and then clicking where you want them to be placed. You can cancel out of this selection by using your right click.</span></span></span></p>

<p><span style="font-family:Tahoma,Geneva,sans-serif"><span style="font-size:11pt"><span style="font-size:12.0pt">The Nuke option will create a massive (and expensive) explosion where you click, killing every monster it reaches.</span></span></span></p>

<p><span style="font-family:Tahoma,Geneva,sans-serif"><span style="font-size:11pt"><span style="font-size:12.0pt">The cube in the middle also has a manual weapon that you can shoot after selecting the cube and holding your right mouse button.</span></span></span></p>

<p>&nbsp;</p>

<p><span style="font-family:Tahoma,Geneva,sans-serif"><span style="font-size:11pt"><strong><span style="font-size:18.0pt">MY PROCESS</span></strong></span></span></p>

<p><span style="font-family:Tahoma,Geneva,sans-serif"><span style="font-size:11pt"><span style="font-size:12.0pt">After I got acclimated a little bit with the framework, I spent some time coming up with a visual design and what I expected the game to play like. I then broke down those ideas into components that I had to implement. I wanted it to stand out visually, so I spent some time building a compatible asset pipeline that allowed me to create my assets in blender and import them in as .Obj files. This access to more visual data allowed me to implement a simple vertex animation framework that would blend between different poses of the same mesh to create motion.</span></span></span></p>

<p><span style="font-family:Tahoma,Geneva,sans-serif"><span style="font-size:11pt"><span style="font-size:12.0pt">The rest was relatively simple. I implemented more &lsquo;game&rsquo; concepts like GameObjects, Monsters, Towers, and Projectiles, as well as some (very) basic UI that would facilitate a gameplay loop.</span></span></span></p>

<p><span style="font-family:Tahoma,Geneva,sans-serif"><span style="font-size:11pt"><span style="font-size:12.0pt">I kept track of the player&rsquo;s funds, only letting them build towers if they&rsquo;re not too close to each other or the monsters&rsquo; path.</span></span></span></p>

<p><span style="font-family:Tahoma,Geneva,sans-serif"><span style="font-size:11pt"><span style="font-size:12.0pt">A spline mesh would be used to describe the path the AI monsters needed to follow, and I designed a simple process that would allow me to plan the monsters&rsquo; spawns for a given level.</span></span></span></p>

<p><span style="font-family:Tahoma,Geneva,sans-serif"><span style="font-size:11pt"><span style="font-size:12.0pt">I finally spent some time making different types of towers and monsters. Due to severe time constraints, I had to cut a few ideas like having multiple levels or sound playback.</span></span></span></p>
