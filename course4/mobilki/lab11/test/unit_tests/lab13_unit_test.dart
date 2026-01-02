import 'package:flutter_test/flutter_test.dart';
import 'package:hotel_app/blocs/auth/auth_bloc.dart';
import 'package:hotel_app/blocs/favorites/favorites_bloc.dart';
import 'package:hotel_app/blocs/hotels/hotels_bloc.dart';
import 'package:hotel_app/favorite.dart';
import 'package:hotel_app/hotel.dart';
import 'package:hotel_app/services/auth_service.dart';
import 'package:hotel_app/services/firestore_service.dart';
import 'package:mockito/annotations.dart';
import 'package:mockito/mockito.dart';

import 'lab13_unit_test.mocks.dart';

@GenerateNiceMocks([
  MockSpec<AuthService>(),
  MockSpec<FirestoreService>(),
])
void main() {

  group('Lab13 Unit Tests (Mockito) — 5 tests', () {
    test('1) Hotel model: price is stored correctly (expect)', () {
      final hotel = Hotel(
        id: 'h1',
        title: 'Hotel',
        place: 'Place',
        price: 123,
        rating: 4.2,
        reviews: '10',
        image: 'https://example.com/img.jpg',
        description: 'Desc',
      );

      expect(hotel.price, 123);
    });

    test('2) HotelsBloc: after LoadHotelsEvent emits Loading then Loaded (expect)', () async {
      final fs = MockFirestoreService();
      when(fs.getHotelsStream()).thenAnswer((_) => Stream<List<Hotel>>.empty());
      when(fs.getHotels()).thenAnswer((_) async => [
            Hotel(
              id: 'h1',
              title: 'Hotel 1',
              place: 'Place 1',
              price: 100,
              rating: 4.5,
              reviews: '100',
              image: 'https://example.com/1.jpg',
              description: 'D1',
            ),
          ]);

      final bloc = HotelsBloc(fs);

      final emitted = <HotelsState>[];
      final sub = bloc.stream.listen(emitted.add);

      await Future<void>.delayed(const Duration(milliseconds: 50));

      expect(emitted.isNotEmpty, isTrue);
      expect(emitted.first, isA<HotelsLoading>());
      expect(emitted.any((s) => s is HotelsLoaded), isTrue);

      await sub.cancel();
      await bloc.close();
    });

    test('3) FavoritesBloc: LoadFavoritesEvent emits Loading then Loaded (expect)', () async {
      final fs = MockFirestoreService();
      when(fs.getFavorites('user_1')).thenAnswer((_) async => []);

      final bloc = FavoritesBloc(fs);
      final emitted = <FavoritesState>[];
      final sub = bloc.stream.listen(emitted.add);

      bloc.add(const LoadFavoritesEvent('user_1'));
      await Future<void>.delayed(const Duration(milliseconds: 50));

      expect(emitted.isNotEmpty, isTrue);
      expect(emitted.first, isA<FavoritesLoading>());
      expect(emitted.any((s) => s is FavoritesLoaded), isTrue);

      await sub.cancel();
      await bloc.close();
    });

    test('4) AuthBloc: SignInWithEmailPasswordEvent emits Loading then Authenticated (expect)', () async {
      final auth = MockAuthService();
      when(auth.signInWithEmailPassword('a@b.com', '123456')).thenAnswer((_) async {});

      final bloc = AuthBloc(auth);
      final emitted = <AuthState>[];
      final sub = bloc.stream.listen(emitted.add);

      bloc.add(const SignInWithEmailPasswordEvent('a@b.com', '123456'));
      await Future<void>.delayed(const Duration(milliseconds: 50));

      expect(emitted.isNotEmpty, isTrue);
      expect(emitted.first, isA<AuthLoading>());
      expect(emitted.any((s) => s is AuthAuthenticated), isTrue);

      await sub.cancel();
      await bloc.close();
    });

    test('5) Favorite model: userId and hotelId match expected (expect)', () {
      final fav = Favorite(
        documentId: 'doc',
        userId: 'u1',
        hotelId: 'h1',
        addedAt: DateTime(2025, 1, 1),
      );

      expect(fav.userId, 'u1');
      expect(fav.hotelId, 'h1');
    });
  });
}


