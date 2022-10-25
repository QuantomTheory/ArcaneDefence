# ArcaneDefence
The c++ files from my Arcane Defence game.

A small 3rd-person defence game. Where the player must hold off the attacking forces for 5 minutes.

I made an effort to break functionality down into components and inherited classes where reasonable. 


Note: A number of the c++ files have the "PorfolioProject" name. This was the initial placeholder name.

Project Overview
This is 3rd-person, single-level game, where the player must defend a point from oncoming enemies, using a number of spell attacks to defeat them.
Built by myself in Unreal Engine 5, using C++, over the course of 3 weeks.
‍
I used what I had learnt so far, as well as numerous new skills gained during the development to solve problems and challenges I encountered.
I built this project with a modular design making use of components and inherited classes to improve scalability and efficiency.

This project was the first game I made end-to-end without any guidance from training courses. I wanted to make something that would require designing and building a number of different gameplay abilities. I started by thinking about what I learned from training courses and how I could expand on it in my own way to create different abilities for the character. I decided on 3 abilities for the character, a basic projectile, a bomb projectile, and a powerful beam attack.
‍
‍
Spell Design:
I began by making the Spell class as a high level parent class for all the other spell classes to inherit from. It contains very little functionality and more serves as a base to allow all children to be related under a similar parent.

Next I made the first child of the Spell class, the Projectile class. This would serve as the parent to both the basic projectile attack and the bomb projectile. It's main functionality is to build out the projectile components (Meshes, Particles, Movement, etc) and to handle the triggering of any particle effects upon Spawn or Destruction.

From this Projectile class I made two further children, the SimpleProjectile and the AoEProjectile classes. The primary difference between these classes is how they deal damage upon collision. The SimpleProjectile uses the UGamplayStatics::ApplyDamage function to only apply damage to the Actor hit. Whereas, the AoEProjectile uses the ApplyRadialDamage function to affect an area.

To make the Beam class I created a separate child class from the Spell class. Instead of using collisions to retrieve affected actors, this uses a shape trace every Tick to determine which actors overlap the beam. The beam is also temporarily attached to the player to allow them to continue to aim for the duration.
‍

Component Creation:
I created a reusable HealthComponent that would manage character/object health, and trigger death once HP reached zero. This could be attached to any actor to give it a customisable health level and track damage received. This was attached to the Player Character, the Enemy Characters, as well as the Defence Point.
‍
The other actor component I created was the InventoryComponent. This was built to manage and track the spells of the player, and to allow for an easily expandable spell list. It makes use of an Array to track the assigned spells as well as numerous timer to independently track each spells cooldown.
‍

Challenges:
While working on this project I faced a number of new challenges. The major challenge was building a way to track the casting of spells and their cooldowns. In the end I resolved this by building the Inventory Component which stores the spells information in an array and manages the timers on each spells cooldown. This also meant that if I wanted to, adding new spells to the spell list would be much easy in the future.
‍
Another challenge was how to make the beam attack work consistently, I initially built this to use an invisible collision mesh and simply apply damage to actors that collided with it. However, this didn't trigger collisions on enemies already within the mesh upon spawning. I therefore decided to use a Shape Trace along the length of the beam for the duration. This brought about another difficulty when I first attempted to use ShapeTraceByChannel as it would be inconsistent when returning the enemies as HitResults, and therefore not consistently damaging them in game. After trying a number of different solutions, such as changing the collision channel or testing Single Trace vs Multi Trace. I eventually found changing it to a ShapeTraceByObjectType worked much more reliably and was able to return the desire effect for the ability.
‍

All Assets, Meshes, Effects and Sounds etc are free resources from the Unreal Engine Marketplace.
