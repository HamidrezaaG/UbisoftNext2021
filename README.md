ABOUT
This was my submission for the Ubisoft NEXT programming challenge in 2021, which I finished in the top 5. The challenge was to make a tower defense game in three days with the code framework provided.
Participants would be able to play audio and render simple 2D line segments and sprites with the base framework.

HOW TO PLAY
The goal is to stop the monsters before they reach the cube in the middle. You achieve this by building towers on their path using your available funds (shown in the top left corner). You get rewarded for killing the monsters.
Click the “start” button to begin the game. You can then place towers by clicking the buttons onscreen and then clicking where you want them to be placed. You can cancel out of this selection by using your right click.
The Nuke option will create a massive (and expensive) explosion where you click, killing every monster it reaches.
The cube in the middle also has a manual weapon that you can shoot after selecting the cube and holding your right mouse button.

MY PROCESS
After I got acclimated a little bit with the framework, I spent some time coming up with a visual design and what I expected the game to play like. I then broke down those ideas into components that I had to implement. I wanted it to stand out visually, so I spent some time building a compatible asset pipeline that allowed me to create my assets in blender and import them in as .Obj files. This access to more visual data allowed me to implement a simple vertex animation framework that would blend between different poses of the same mesh to create motion.

The rest was relatively simple. I implemented more ‘game’ concepts like GameObjects, Monsters, Towers, and Projectiles, as well as some (very) basic UI that would facilitate a gameplay loop.

I kept track of the player’s funds, only letting them build towers if they’re not too close to each other or the monsters’ path. A spline mesh would be used to describe the path the AI monsters needed to follow, and I designed a simple process that would allow me to plan the monsters’ spawns for a given level.

I finally spent some time making different types of towers and monsters. Due to severe time constraints, I had to cut a few ideas like having multiple levels or sound playback.
