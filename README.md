# multiple-checkpoints-samp
This include lets you create more than one checkpoint at the same time!

# How to install:
Just copy and paste Cps.inc into your pawno/include folder and use #include <Cps.inc> in your script after including a_samp and streamer

# Functions:

#### ShowCP(playerid, Float:x, Float:y, Float:z)
>* **Parameters:**

>       playerid - The id of the player to create checkpoint for
>       Float:x, Float:y, Float:z - The position of the checkpoint
>* **Returns:**

>       INVALID_CP_ID(-1) if failed to create the checkpoint
>       The id of the checkpoint if successful
>* **Remarks:**

>       It will print an error message if it fails to create the checkpoint(player is not connected or there's no available free map icon for that player)

#### DestroyCP(playerid, cpid)
>* **Parameters:**

>       playerid - The id of the player to destroy the checkpoint for
>       cpid - The id of the checkpoint to destroy(Returned by ShowCP)
>* **Returns:**

>       0 if didn't execute successfully(Invalid checkpoint id)
>       1 if function executed successfully
>* **Remarks:**

>       It will print an error message if it fails to destroy the checkpoint(cpid is invalid or player is not connected)

# Callbacks:

#### OnPlayerEnterCP(playerid, cpid)
>* **Parameters:**

>       playerid - The id of the player who triggered the checkpoint
>       cpid - The id of the checkpoint player has triggered

#### OnPlayerLeaveCP(playerid, cpid)
>* **Parameters:**

>       playerid - The id of the player who triggered the checkpoint
>       cpid - The id of the checkpoint player has triggered
