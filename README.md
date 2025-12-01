<a id="readme-top"></a>
![A portrait of Alex Hoffman, along with the covers to video games Forza Motorsport, Life Is Strange: True Colors, H1Z1, and PlanetSide 2][title-image]

<!-- PROJECT LOGO -->
<br />

<div align="center">
<h3 align="center">Proximity Radar</h3>
	<p align="center">
    A small UE5 project showcasing a UI element that helps racing while in first person.
    <br />
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li><a href="#My-Contributions">My Contributions</a></li>
    <li><a href="#installation">Installation</a></li>
    <li><a href="#contact">Contact</a></li>
	<li><a href="#media">Media</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project
![Proximity Radar screenshot][sample-screenshot]

Proximity Radar is a UI element, driven by C++ data, that shows the player all the cars nearby. The goal is to give the player awareness of nearby cars with precision, so as to facilitate cleaner racing. Especially for players with steering wheel setups, racing in a first person view is a must. However, most players only have a single screen, so this limits their awareness that a third person view would provide. Without this extra awareness, racers run the risk of crashing into other cars. So it was necessary to create awareness of the cars around the player, and Proximity Radar was the solution. Simply put, Proximity Radar is a top down minimap for the player.

Proximity Radar is one of my proudest achievements in Forza Motorsport. You can see that version [here](https://x.com/ForzaMotorsport/status/1812895088571195739). It was a system I advocated for as a competivie Forza player. During my time at Turn 10 and Microsoft, I saw it through from concept to completion. I was responsible for making the prototype, creating technical documentation, leading a feature team, testing, and the actual C++ implementation. It released to praise from players as a welcome addition. I take a lot of pride in that reception, as it was a highly requested feature, and it delivered on what the players wanted.

As it's one of my favorite features, I decided to re-create it in Unreal Engine 5. I wanted to have it as a small portfolio piece.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## My Contributions
I started with the default Vehicle project in Unreal Engine ver 5.6.1. The following files have my contributions:

[ProximityModule.cpp](Source/ProximityRadar/Private/ProximityModule.cpp) - This is the main brains of the radar. It grabs all the cars, sorts them by distance, and rotates their locations about the players forward vector. This gives a top down, 2D view of the cars around the player, almost like a minimap. The file is commented, so further detail can be found within.

[ProximityModule.h](Source/ProximityRadar/Public/ProximityModule.h) - The header for the above file.

[RadarTypes.h](Source/ProximityRadar/Public/RadarTypes.h) - The location for distance to process cars for the radar, and the distances to draw the red and yellow blindspot arcs. In a real game, I would put these in a spot that would be easier for a desinger to change, as changing these would require a code recompile. As this is Unreal, I would put them in a blueprint so a designer could easily access and modify them. But I wanted them to be visible easily here on github.

[ProximityRadarUI.cpp](Source/ProximityRadar/ProximityRadarUI.cpp) - Mainly an unreal contribution, but my changes have been marked with `// AlexHoffman addition`. I pass along the processed car locations to the UI blueprint for moving and displaying.

[ProximityRadarUI.h](Source/ProximityRadar/ProximityRadarUI.h) - The header for the above file.

[ProximityRadarPlayerController.cpp](Source/ProximityRadar/ProximityRadarPlayerController.cpp) - Mainly an Unreal contribution, but my changes have been marked with `// AlexHoffman addition`. I created the proximity module on the player, as the player is what will manage and process the cars surrounding it. It's where Unreal dedcided the UI should be created, so I followed their lead for simplicity.

[ProximityRadarPlayerController.h](Source/ProximityRadar/ProximityRadarPlayerController.h) - The header for the above file.

I created all the UI assets by myself using Clip Studio Paint.

I also have a list of not so visible changes from the UE5 vehicle project: 
* Added pause menu
* Changed track and terrain to be more interesting than the default circle
* Splines for custom CarActor to follow, along with offsets so multiple cars can follow same path
* Radar UI is largely handled in the blueprint

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Installation

1. Download the windows package [here](https://drive.google.com/file/d/13n8Bs8Yz2dhaBchqZzzsRIYNT4WpMMzc/view?usp=sharing)
2. Open the Windows folder and look for ProximityRadar.exe
3. Run the exe

## Controls
Tab - Change camera view to hood or third person

Esc or P - Pause the game

W - Throttle

S - Brake

A/D - Left Right steering
	
## Media 
![Proximity Radar gif][sample-gif]

You can see a gameplay video here (to be added).
[![Youtube Video][yt-thumb]](https://youtu.be/DPtOh4iYAig)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

Alex Hoffman アレックス・ホフマン - [LinkedIn](https://www.linkedin.com/in/alexh9/)

[MobyGames Credits](https://www.mobygames.com/person/478509/alex-hoffman/) - This list is missing my credits from PlanetSide Arena and Life is Strange Remaster.

My resume, email, and other contact information available upon request.

<p align="right">(<a href="#readme-top">back to top</a>)</p>




<!-- MARKDOWN LINKS & IMAGES -->
[linkedin-url]: https://www.linkedin.com/in/alexh9/
[sample-screenshot]: Media/SampleImage.png
[yt-thumb]: Media/thumbnail.png
[sample-gif]: Media/ProximityRadarGif.gif
[title-image]: Media/TitleImage.png
