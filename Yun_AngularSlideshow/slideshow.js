angular.module('slideshow', [])

.controller('SlideshowController', function($scope, $timeout, $http) {
    var pictures = ['1375995225.png', '1375995954.png'];
    var delay = 2000;
    var checkForNewPicturesDelay = 30000;
    var currentPictureIndex = 0;

    $scope.currentPicture = pictures[currentPictureIndex];

    $scope.nextPicture = function() {
        currentPictureIndex++;
        if (currentPictureIndex == pictures.length) {
            currentPictureIndex = 0;
        }
        $scope.currentPicture = pictures[currentPictureIndex];
    };

    function iteratePictures() {
        $scope.nextPicture();
        $timeout(iteratePictures, delay);
    }
    $timeout(iteratePictures, delay);

    function checkForNewPictures() {
        return $http.get('picturesList.txt')
            .success(function(data) {
                pictures = data.split('\n');
                pictures.pop();
                $timeout(checkForNewPictures, checkForNewPicturesDelay);
            });
    }
    checkForNewPictures();
});