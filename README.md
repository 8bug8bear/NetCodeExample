# Net code example
This project is my coursework, in which I needed to create a simple network shooter. In this project, I fully used all my project architecture building skills as well as my skills working with UE4 network tools. The game is based on client-server interaction technology and the use of predicates on clients.

At the start, the player is greeted by a simple visual interface offering to find a dedicated server and connect to it, or to play a game.

![2022-07-03_01-32-31](https://user-images.githubusercontent.com/67451613/184465667-99c8513b-fc55-4b79-ab33-30296c86efbf.png)

At the same time, a dedicated server must be running on one of the local machines. The connection is made directly by IP.

![2022-07-03_01-34-29](https://user-images.githubusercontent.com/67451613/184465706-3cb253c0-5b2c-46cb-af75-13176e137451.png)

The gameplay is built on the basis of the every man for himself mode. All players, as they connect to the server, will spawn on the map. They have one weapon (a submachine gun). Players can jump, shoot, aim and run, while running, you can not aim and shoot, and if you run while shooting or aiming, then shooting or aiming will stop. Players can also jump and aim weapons. When a player is hit, his health bar in the lower left corner decreases. When a player runs out of health, he dies and is instantly resurrected at one of the resurrection points.

![2022-07-03_01-30-51](https://user-images.githubusercontent.com/67451613/184465731-c043fdfd-c5b8-4a3e-986d-e464c5b6ddf3.png)

![2022-07-03_01-31-24](https://user-images.githubusercontent.com/67451613/184465738-1d9d6d36-a8cb-472c-8b2f-38859671351a.png)

In the pictures you can see how client 1 aims and shoots.
