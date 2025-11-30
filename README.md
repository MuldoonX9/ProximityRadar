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

Proximity Radar is one of my proudest achievements in Forza Motorsport. You can see that version [here](https://x.com/ForzaMotorsport/status/1812895088571195739). It was a system I advocated for as a competitive fan of Forza. I saw it through from concept to completion. I was responsible for making the prototype, creating technical documentation, leading a feature team, testing, and the actual C++ implementation. 

As it's one of my favorite features, I decided to re-create it in Unreal Engine 5. I wanted to have it as a small portfolio piece. 

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## My Contributions
The following files have my contributions:

[ProximityModule.cpp](Source/ProximityRadar/Private/ProximityModule.cpp) - This is the main brains of the radar.

[RadarTypes.h](Source/ProximityRadar/Public/RadarTypes.h) - In a real game, I would put these in a spot that would be easier for a desinger to change. Since this is Unreal, I would put them in a blueprint so a designer could easily access and modify them. But I wanted them to be visible easily here on github.

I created all the UI assets by myself using Clip Studio Paint.

I also have a list of not so visible changes from the UE5 vehicle project: 
* Added pause menu
* Changed track and terrain to be more interesting than the default circle
* Splines for custom CarActor to follow, along with offsets so multiple cars can follow same path
* Radar UI is largely handled in the blueprint

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
You can see a gameplay video here (to be added).

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
[title-image]: Media/TitleImage.png
