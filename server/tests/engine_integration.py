import unittest
from lib.pystation import *

class TestEngineIntegration(unittest.TestCase):

    spi_file_path = 'C:/Users/Ahmed Mustafa/Desktop/acture-server/server/tests/test_data/test.spi'


    def setUp(self):
        engine = Engine()
        self.assertIsInstance(engine, Engine)

    def test_initial_time(self):
        engine = Engine()
        self.assertEqual(engine.get_current_time(), 0.0)

    def test_deserialize_spi_file(self):
        engine = Engine()

        
        deserializer = StationNetworkSerializer(engine)
        deserializer.import_spi_file(self.spi_file_path)

        self.assertEqual(engine.get_station_network().size(), 4)
        self.assertIsNotNone(engine.get_media_binder().get_verse())

    def test_media_binder_operations(self):
        engine = Engine()
        
        deserializer = StationNetworkSerializer(engine)
        deserializer.import_spi_file(self.spi_file_path)

        media_binder = engine.get_media_binder()
        active_verse = media_binder.get_verse()

        self.assertIsNotNone(active_verse)

        clips_count = active_verse.tracks[0].get_clip_count()
        self.assertGreater(clips_count, 0)

        clip = active_verse.tracks[0].get_clip(0)

        self.assertIsInstance(clip, VideoClip)

    def test_media_binding(self):
        engine = Engine()
        deserializer = StationNetworkSerializer(engine)
        deserializer.import_spi_file(self.spi_file_path)
        media_binder = engine.get_media_binder()

        self.assertIsInstance(media_binder.get_verse(), Verse)

        clips = media_binder.data_to_bind(0)

        self.assertGreaterEqual(len(clips), 1)

        self.assertIsInstance(clips[0], VideoClip)
        print(clips[0].to_dict())

if __name__ == '__main__':

    suite = unittest.TestLoader().loadTestsFromTestCase(TestEngineIntegration)
    runner = unittest.TextTestRunner(verbosity=2)
    result = runner.run(suite)
