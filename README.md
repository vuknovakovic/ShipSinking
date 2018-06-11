# RG060-potapanje-brodica
# Student: Vuk Novakovic


## Installing:

``` 
git clone https://github.com/MATF-RG17/RG060-potapanje-brodica.git
cd RG060-potapanje-brodica
make (make -j for faster compilation)
./ships
```

## Game consists of two phases:
### Phase 1: Adding ships
    Every player has 10 ships total:
    
    4 ships of size 1
    
    3 ships of size 2
    
    2 ships of size 3
    
    1 ship of size 4
    
    player 1 places his ships on the left field, when he is done player 2 places his on right field
    
    everything is done using mouse and mouse click
    
    use 'r' to rotate ship (horizontal or vertical)
    
    
### Phase 2: Aiming
    Aiming is done using mouse and mouse click.
    
    If player hits enemy ship, he gets to aim again
    
    player 1 aims first(he aims on right field since there are ships of player 2)
    player 2 aims after him
    
    Winner is player which destroys enemy ships
    
## Legend:
Gray field represents aimed cell, but missed (no ship was there).

Sphere represents hit part of a ship.

When ship is destroyed (all of its cells are hit) it is shown in red.
