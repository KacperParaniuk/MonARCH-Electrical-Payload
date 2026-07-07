Created By Kacper Paraniuk 07-06-26 


This is a markdown file containing the commands for cli of the payload interface board 



Each command will begin with pib. This is used to verify the command 


The command structure is:

pib <verb> <target>


COMMANDS:

Sensors 
-----------------------------------------------------------------------------------------------------------

pib <verb> <target[num]>

ex: pib read temp1 
    pib read pressure2



Actions 
-----------------------------------------------------------------------------------------------------------
pib <verb> <target[num]>

ex: pib open valve3


Events -----------------------------------------------------------------------------------------------------------

pib <verb> <event>

ex: pib run accumulator_fill


