# Zeleni Fitnes
#### Video Demo: https://youtu.be/FFarahM3Zm8
#### Description:
For my final project, I decided to create a website called Zeleni Fitnes, which translates to Green Fitness. The reason why I chose to develop a fitness website is to provide my brother, who owns a fitness center called Zeleni Fitnes, with a platform where he can independently post and edit events with a sign-in feature. The main purpose of the website is to upload upcoming events, but it also allows people to view the opening hours, pricing information, and contact details of the fitness center. All of my website content is in Slovenian because Zeleni Fitnes is a local fitness center in the Slovenian Alps, and I did not see the need to add a different language.

### Code behind the website
My code contains HTML, JavaScript, Python, CSS, Flask, Jinja and SQLite.

My Python file, app.py, creates/edits/selects/deletes data from my database, which I created using SQLite. It ensures that Jinja works properly by utilizing the web application framework Flask, written in Python. It also checks the password and username for signing in to edit events.

On my website, I have also added a toggle switch to switch between dark and light themes. To enable this toggle, I have a JavaScript and CSS file. For styling on my website, I mostly used Bootstrap, and for icons, I used Font Awesome.

Since I am using Jinja, I have quite a few HTML files. The "frame" of my website is defined in layout.html, which contains the header, navigation, and footer where all the contact information is stored, along with a login button. The body of the website changes based on the page. By default, it uses index.html, where events are displayed in order of date. It also provides static information about opening hours and pricing. If a user wants to log in, the main context changes to login.html. If the password and username are correct, the user is taken to editevent.html, where they can create and delete events. In the contacts section, all the contact details are also links. Clicking on the location opens a new tab with Google Maps showing the location. Clicking on the phone number automatically inputs the number, ready to call. Clicking on the email automatically opens the user's email client with the email address pre-filled.

### Acess to edit website

In order to minimize my future involvement in maintaining my brother's business website, I have taken measures to ensure that he can handle all aspects of it independently. To achieve this, I have implemented a user-friendly login system that grants access based on a unique username and a dynamically generated password.

To log in, users are required to enter a username that I have specifically created for my brother, based on his nickname, "ALI." This ensures that only authorized individuals can access the website. By using his familiar nickname as the username, it enhances usability and reduces the chances of forgetting or mistyping it.

The password, on the other hand, is constructed in a way that it changes dynamically based on the current time, specifically the hours and minutes. This time-based password variation adds an extra layer of security to the system. By leveraging the constantly changing nature of time, it becomes more challenging for unauthorized individuals to gain access to the website.

Furthermore, this login system is designed with scalability in mind. If there is a need to add other users with different levels of access in the future, I can easily configure the system to accommodate them. By assigning different access levels to each user, my brother can control the permissions and privileges granted to different individuals. This allows for flexible management of the website's backend and ensures that each user has access to the appropriate resources and functionalities.

Overall, this login system simplifies the process for my brother to manage the website independently, while also enhancing security measures and providing a framework for potential future expansion.

### Future for the website

This website will be initially published using GitHub as the hosting platform. GitHub provides a convenient and reliable way to showcase and manage the website's codebase. Once the website is ready for launch, we will generate a unique website link that can be accessed by users.

To promote the website, we plan to create a QR code that will be prominently displayed in fitness centers and various locations throughout the town. The QR code will provide a quick and convenient way for people to access the website using their smartphones. By placing the QR code strategically, we can attract potential clients and generate interest in my brother's physiotherapy services.

As my brother is currently studying physiotherapy, we have plans to expand the website in the future to serve as a comprehensive platform for his business. This expansion will involve incorporating various features and functionalities that cater specifically to the needs of his profession. The website will become a central hub where clients can access information about his services, schedule appointments, read informative articles, and potentially even participate in interactive sessions or receive personalized recommendations.

While the website is still a work in progress, I am fully committed to continuously improving and expanding it. I understand that there is a lot of work ahead to ensure the website meets the highest standards and provides an exceptional user experience. I will be dedicating my efforts to refine the design, optimize the performance, enhance the functionality, and incorporate valuable content to make the website a valuable resource for users.